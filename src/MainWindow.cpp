#include "MainWindow.h"

#include <QTableView>
#include <QHeaderView>
#include <QDockWidget>
#include <QtConcurrent>
#include <QDir>
#include <QFile>

#include "LogWidget.h"

MainWindow::MainWindow()
{
    resize(1000, 700);

    auto view = new QTableView;
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _model = new EverythingModel(this);
    view->setModel(_model);
    setCentralWidget(view);

    auto logDock = new QDockWidget(QStringLiteral("Log"), this);
    logDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    logDock->setWidget(new LogWidget(logDock));
    addDockWidget(Qt::BottomDockWidgetArea, logDock);

    auto searchDock = new QDockWidget(QStringLiteral("Search File"), this);
    searchDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    _searchWidget = new SearchWidget(searchDock);
    searchDock->setWidget(_searchWidget);
    addDockWidget(Qt::LeftDockWidgetArea, searchDock);

    connect(_searchWidget, &SearchWidget::filterChanged, _model, &EverythingModel::setFilter);
    connect(_searchWidget, &SearchWidget::doRenameFiles, this, &MainWindow::renameFiles);
}

MainWindow::~MainWindow()
{
}

void MainWindow::renameFiles()
{
    _searchWidget->setEnabled(false);

    QHash<QString, QString> files;
    auto match = _searchWidget->fileMatch();
    auto replace = _searchWidget->fileReplace();

    {
        auto rowCount = _model->rowCount();

        for (int i = 0; i < rowCount; ++i)
        {
            auto fileName = _model->data(_model->index(i, 0)).toString();
            if (fileName.contains(match))
            {
                auto filePath = _model->data(_model->index(i, 1)).toString();
                auto src = QDir(filePath).absoluteFilePath(fileName);
                if (!QFileInfo(src).isFile())
                {
                    continue;
                }

                files.insert(src, QDir(filePath).absoluteFilePath(QString(fileName).replace(match, replace)));
            }
        }
    }

    qInfo().noquote() << QString("Renaming %1 files matching '%2' to '%3'").arg(files.size()).arg(match).arg(replace);
    QtConcurrent::run([this, files]
                      {
                        for (auto it = files.cbegin(); it != files.cend(); ++it) {
                            qInfo().noquote() << "Renaming" 
                                << QStringLiteral("<%1>").arg(it.key()) << "to" 
                                << QStringLiteral("<%2>").arg(it.value());

                            if (!QFile::rename(it.key(), it.value())) {
                                qWarning().noquote() << "Failed to rename" 
                                    << QStringLiteral("<%1>").arg(it.key()) << "to" 
                                    << QStringLiteral("<%2>").arg(it.value());
                            }
                        }
                        
                        qInfo().noquote() << "Renaming complete";
                        QMetaObject::invokeMethod(this, [this]
                                                  { _searchWidget->setEnabled(true); 
                                                  _model->setFilter(_searchWidget->filter()); }); });
}
