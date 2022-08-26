#include "progressdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProgressDialog w;
    w.show();
    return a.exec();
}
