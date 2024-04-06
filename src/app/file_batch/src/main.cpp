#include <QApplication>
#include <QWidget>
#include <QDebug>

#include <everything_sdk/Everything.h>

void test_everything()
{
    Everything_SetSearch("123");
    Everything_Query(TRUE);

    qDebug() << Everything_GetNumResults();

    for (int i = 0; i < Everything_GetNumResults(); i++)
    {
        // qDebug() << Everything_GetResultFileName(i);
        // qDebug() << Everything_GetResultPath(i);
        // qDebug() << Everything_GetResultFullPathName(i);
    }
}

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    test_everything();
    QWidget w;
    w.show();
    return a.exec();
}