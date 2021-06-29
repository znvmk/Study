#include "mainwindow.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(300,300);
    QLabel* label=new QLabel(&w);
    label->setText("Hello World! 你好Qt！");
    label->resize(120,100);
    label ->move(90,80);
    w.show();
    return a.exec();
}

