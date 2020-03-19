#include "dialog.h"
#include <QApplication>
#include "content.h"
#include <QTextCodec>
#include <QSplitter>
#include <QListWidget>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("AR PL KaitM GB",12);
    a.setFont(font);

    QSplitter* splitterMain=new QSplitter(Qt::Horizontal,nullptr);
    splitterMain->setOpaqueResize(true);
    QListWidget* list=new QListWidget(splitterMain);

    list->insertItem(0,QString::fromLocal8Bit("基本信息"));
    list->insertItem(0,QString::fromLocal8Bit("联系方式"));
    list->insertItem(0,QString::fromLocal8Bit("详细资料"));

    Content* content=new Content(splitterMain);
    QObject::connect(list,SIGNAL(currentRowChange(int)),content->stack,
                     SLOT(setCurrentIndex(int)));
    splitterMain->setWindowTitle(QString::fromLocal8Bit("修改用户资料"));
    splitterMain->setMinimumSize((splitterMain->minimumSize()));
    splitterMain->setMaximumSize(splitterMain->maximumSize());
    splitterMain->show();

    //Dialog w;
    //w.show();

    return a.exec();
}
