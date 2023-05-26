#include "extensiondialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExtensionDialog w;
    w.show();
    return a.exec();
}
