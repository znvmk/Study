#include "mainwindow.h"
#include <QApplication>
#include <mywidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(100,100,200,120);
    w.show();

    return a.exec();
}
