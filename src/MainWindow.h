#pragma once
#include <QMainWindow>

#include "SearchWidget.h"
#include "EverythingModel.h"

class MainWindow : public QMainWindow
{
public:
    MainWindow();
    ~MainWindow();

private slots:
    void renameFiles();
    void replaceTexts();

private:
    SearchWidget *_searchWidget{nullptr};
    EverythingModel *_model{nullptr};
};
