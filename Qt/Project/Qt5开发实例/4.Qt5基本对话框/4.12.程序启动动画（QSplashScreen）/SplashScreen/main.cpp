#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/1.jpg");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();
    MainWindow w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
//需要添加新文件，资源，在资源中添加图片。加载图片用：(":/*.jpg")
