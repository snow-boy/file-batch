#include <QApplication>
#include "Logger.h"
#include "MainWindow.h"

int main(int argc, char **argv)
{
    Logger::init();

    QApplication a(argc, argv);
    MainWindow mw;
    mw.show();
    return a.exec();
}