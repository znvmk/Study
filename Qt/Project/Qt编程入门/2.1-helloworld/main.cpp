#include "mainwindow.h"
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(400, 300);
    QLabel *label = new QLabel(&w);
    label->setText("Hello world ! 你好Qt ！");
    label->resize(200, 20);
    label->move(120, 120);
    w.show();
    return a.exec();
}
