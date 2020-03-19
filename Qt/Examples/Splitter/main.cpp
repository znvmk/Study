#include "mainwindow.h"
#include <QApplication>
#include <QSplitter>
#include <QTextEdit>
#include <QDockWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font("ZYSong18030",12);
    a.setFont(font);
    //主分割窗口
    QSplitter* splitterMain=new QSplitter(Qt::Horizontal,nullptr);
    QTextEdit* textLeft=new QTextEdit(QObject::tr("Left Widget"),splitterMain);
    textLeft->setAlignment(Qt::AlignCenter);
    //右边分割窗口
    QSplitter* splitterRight=new QSplitter(Qt::Vertical,splitterMain);
    splitterMain->setOpaqueResize(false);
    QTextEdit *textUp=new QTextEdit(QObject::tr("Top Widget"),splitterRight);
    textUp->setAlignment(Qt::AlignCenter);
    QTextEdit* textBottom=new QTextEdit(QObject::tr("Bottom Widget"),splitterRight);
    textBottom->setAlignment(Qt::AlignCenter);
    splitterMain->setStretchFactor(1,1);
    splitterMain->setWindowTitle(QObject::tr("Splitter"));

    //显示分割窗口
    splitterMain->show();

    //显示第二个窗口，停靠窗口：dock
    MainWindow w;
    w.show();

    return a.exec();
}
