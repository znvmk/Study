#include "mainwindow.h"
//#include "dialog.h"
#include <QApplication>
#include "drawer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    Drawer drawer;
    drawer.show();


    return a.exec();
}
