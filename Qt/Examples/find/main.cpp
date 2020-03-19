#include "mainwindow.h"
#include <QApplication>
#include "FindDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FindDialog *dialog=new FindDialog;
    dialog->show();

    //MainWindow w;
    //w.show();

    return a.exec();
}
