#pragma once

#include <QWidget>
#include <QLineEdit>

class SearchWidget : public QWidget
{
    Q_OBJECT
public:
    SearchWidget(QWidget *parent);
    ~SearchWidget();

    QString filter() const
    {
        return _filterEdit->text();
    }

    QString fileMatch() const
    {
        return _fileMatchEdit->text();
    }

    QString fileReplace() const
    {
        return _fileReplaceEdit->text();
    }

    QString textMatch() const
    {
        return _textMatchEdit->text();
    }

    QString textReplace() const
    {
        return _textReplaceEdit->text();
    }

signals:
    void filterChanged(const QString &text);
    void doRenameFiles();
    void doReplaceTexts();

private:
    QLineEdit *_filterEdit{nullptr};
    QLineEdit *_fileMatchEdit{nullptr};
    QLineEdit *_fileReplaceEdit{nullptr};
    QLineEdit *_textMatchEdit{nullptr};
    QLineEdit *_textReplaceEdit{nullptr};
};
