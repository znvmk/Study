#include "dialog.h"
#include "inputdlg.h"

#include <QApplication>
//#include <qtextcodec.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();


    //QTextCodec::setCodecFor
    return a.exec();
}
