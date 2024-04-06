#include "IFileProcessor.h"

#include <QAxObject>
#include <QDebug>

namespace
{
    class WordProcessor : public IFileProcessor
    {
    public:
        static WordProcessor *getInstance()
        {
            static WordProcessor instance;
            return &instance;
        }

        bool replace(const QString &file, const QString &match, const QString &replace) override
        {
            QAxObject word = QAxObject("Word.Application");

            word.setProperty("Visible", false);
            QAxObject *docs = word.querySubObject("Documents");
            docs->dynamicCall("Open(QString)", QString(file).replace("/", R"(\)"));

            QAxObject *doc = word.querySubObject("ActiveDocument");
            if (!doc)
            {
                qWarning().noquote() << "Could not get document";
                return false;
            }

            QAxObject *range = doc->querySubObject("Content");
            if (!range)
            {
                qWarning().noquote() << "Could not get range";
                return false;
            }

            QAxObject *find = range->querySubObject("Find");
            if (!find)
            {
                qWarning().noquote() << "Could not get find";
                return false;
            }

            bool bMatchCase = false;
            bool bMatchWholeWord = false;
            bool bMatchWildCards = false;
            bool bReplaceAll = true;

            QVariantList vl = {match, bMatchCase, bMatchWholeWord, bMatchWildCards, false, false, true, 1, false, replace, bReplaceAll ? "2" : "1"};
            find->dynamicCall("Execute(QString,bool,bool,bool,bool,bool,bool,int,bool,QString,int)", vl);

            docs->dynamicCall("Save()");
            docs->dynamicCall("Close()");
            word.dynamicCall("Quit()");

            return true;
        }
    };

    class ExcelProcessor : public IFileProcessor
    {
    public:
        static ExcelProcessor *getInstance()
        {
            static ExcelProcessor instance;
            return &instance;
        }

        bool replace(const QString &file, const QString &match, const QString &replace) override
        {
            QAxObject excel = QAxObject("Excel.Application");
            excel.setProperty("Visible", false);

            QAxObject *workbooks = excel.querySubObject("Workbooks");
            if (!workbooks)
            {
                qWarning() << "Could not get workbooks";
                return false;
            }

            QAxObject *workbook = workbooks->querySubObject("Open(QString)", QString(file).replace("/", R"(\)"));
            if (!workbook)
            {
                qWarning() << "Could not open workbook:" << file;
                return false;
            }

            QAxObject *sheets = workbook->querySubObject("Sheets");
            if (!sheets)
            {
                qWarning() << "Could not get sheets";
                return false;
            }

            auto sheetCount = sheets->property("Count").toInt();

            for (int i = 1; i <= sheetCount; ++i)
            {
                QAxObject *worksheet = sheets->querySubObject("Item(int)", i);
                if (!worksheet)
                {
                    qWarning() << "Could not get worksheet" << i;
                    continue;
                }

                QAxObject *cells = worksheet->querySubObject("Cells");
                if (!cells)
                {
                    qWarning() << "Could not get cells";
                    continue;
                }

                QAxObject *find = cells->querySubObject("Find(const QVariant&)", match);
                if (!find)
                {
                    qWarning() << "Could not find match";
                    continue;
                }

                QAxObject *rows = find->querySubObject("Rows");
                int rowCount = rows->property("Count").toInt();

                QAxObject *columns = find->querySubObject("Columns");
                int colCount = columns->property("Count").toInt();

                for (int row = 1; row <= rowCount; ++row)
                {
                    for (int col = 1; col <= colCount; ++col)
                    {
                        QAxObject *cell = find->querySubObject("Item(int, int)", row, col);
                        if (!cell)
                        {
                            qWarning() << "Could not get cell" << row << col;
                            continue;
                        }

                        auto cellValue = cell->property("Value");
                        if (cellValue.type() != QMetaType::QString)
                        {
                            qWarning() << "Cell value is not a string" << row << col;
                            continue;
                        }

                        auto cellString = cellValue.toString();
                        if (cellString.contains(match))
                        {
                            cell->setProperty("Value", cellString.replace(match, replace));
                        }
                    }
                }
            }

            workbook->dynamicCall("Save()");
            workbook->dynamicCall("Close()");
            excel.dynamicCall("Quit()");

            return true;
        }
    };
}

IFileProcessor *IFileProcessor::get(const QString &suffix)
{
    if (suffix == QStringLiteral("doc"))
    {
        return WordProcessor::getInstance();
    }
    if (suffix == QStringLiteral("docx"))
    {
        return WordProcessor::getInstance();
    }
    if (suffix == QStringLiteral("xls"))
    {
        return ExcelProcessor::getInstance();
    }
    if (suffix == QStringLiteral("xlsx"))
    {
        return ExcelProcessor::getInstance();
    }
    return nullptr;
}
