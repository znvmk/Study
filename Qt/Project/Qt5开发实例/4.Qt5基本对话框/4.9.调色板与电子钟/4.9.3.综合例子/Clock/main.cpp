#include "dialog.h"
#include "digiclock.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    //w.show();
    DigiClock clock;
    clock.show();
    return a.exec();
}
