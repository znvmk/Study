#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromLocal8Bit("各种标准对话框的实例"));


    //文件标准对话框
    fileBtn=new QPushButton();
    fileBtn->setText(QString::fromLocal8Bit("文件标准对话框实例"));
    fileLineEdit=new QLineEdit();


    //颜色标准对话框
    colorBtn=new QPushButton();
    colorBtn->setText(QString::fromLocal8Bit("颜色标准对话框实例"));
    colorFrame=new QFrame();
    colorFrame->setFrameShape(QFrame::Box);
    colorFrame->setAutoFillBackground(true);


    //字体标准对话框
    fontBtn=new QPushButton();
    fontBtn->setText(QString::fromLocal8Bit("字体标准对话框实例"));
    fontLineEdit=new QLineEdit();
    fontLineEdit->setText(QString::fromLocal8Bit("欢迎使用标准字体对话框！"));

    //布局设计
    mainLayout=new QGridLayout(this);
    mainLayout->addWidget(fileBtn,0,0);
    mainLayout->addWidget(fileLineEdit,0,1);

    mainLayout->addWidget(colorBtn,1,0);
    mainLayout->addWidget(colorFrame,1,1);

    mainLayout->addWidget(fontBtn,2,0);
    mainLayout->addWidget(fontLineEdit,2,1);
    //事件关联
    connect(fileBtn,SIGNAL(clicked()),this,SLOT(showFile()));
    connect(colorBtn,SIGNAL(clicked()),this,SLOT(showColor()));
    connect(fontBtn,SIGNAL(clicked()),this,SLOT(showFont()));

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::showFile()
{
    QString s=QFileDialog::getOpenFileName(this,"open file dialog","/","C++ files(*.cpp)::C files(*.c)::Head files(*.h)");
    fileLineEdit->setText(s);
}
void Dialog::showColor()
{
    QColor c=QColorDialog::getColor(Qt::blue);
    if(c.isValid())
    {
        colorFrame->setPalette(QPalette(c));
    }
}
void Dialog::showFont()
{
    bool ok;
    QFont f=QFontDialog::getFont(&ok);
    if(ok)
    {
        fontLineEdit->setFont(f);
    }
}
