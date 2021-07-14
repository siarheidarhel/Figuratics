#include "mainwindow.h"
#include <mytextclass.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QPalette myPallete (Qt::red,Qt::lightGray);
    a.setPalette(myPallete);
    w.show();

    return a.exec();
}
