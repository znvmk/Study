#include "dialog.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QMessageBox>
#include <QPainter>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("各种标准对话框实例"));

    //文件标准对话框
    fileBtn=new QPushButton;
    fileBtn->setText(tr("文件标准对话框实例"));
    fileLineEdit=new QLineEdit;

    //颜色标准对话框
    colorBtn=new QPushButton();
    colorBtn->setText(tr("颜色标准对话框实例"));
    colorFrame=new QFrame;
    colorFrame->setFrameShape(QFrame::Box);
    colorFrame->setAutoFillBackground(true);

    //字体标准对话框
    fontBtn=new QPushButton;
    fontBtn->setText(tr("字体标准对话框实例"));
    fontLineEdit=new QLineEdit();
    fontLineEdit->setText(tr("Welcome!"));

    //标准输入对话框
    inputBtn=new QPushButton;
    inputBtn->setText(tr("标准输入对话框实例"));

    //标准消息对话框
    MsgBtn=new QPushButton;
    MsgBtn->setText(tr("标准消息对话框"));

    //自定义消息对话框
    CustomBtn=new QPushButton;
    CustomBtn->setText(tr("用户自定义消息对话框实例"));
    label=new QLabel;
    label->setFrameStyle(QFrame::Panel|QFrame::Sunken);


    //布局管理
    mainLayout=new QGridLayout(this);

    mainLayout->addWidget(fileBtn,0,0);
    mainLayout->addWidget(fileLineEdit,0,1);

    mainLayout->addWidget(colorBtn,1,0);
    mainLayout->addWidget(colorFrame,1,1);

    mainLayout->addWidget(fontBtn,2,0);
    mainLayout->addWidget(fontLineEdit,2,1);

    mainLayout->addWidget(inputBtn,3,0);

    mainLayout->addWidget(MsgBtn,3,1);

    mainLayout->addWidget(CustomBtn,4,0);
    mainLayout->addWidget(label,4,1);



    //事件关联
    connect(fileBtn,SIGNAL(clicked()),this,SLOT(showFile()));
    connect(colorBtn,SIGNAL(clicked()),this,SLOT(showColor()));
    connect(fontBtn,SIGNAL(clicked()),this,SLOT(showFont()));
    connect(inputBtn,SIGNAL(clicked()),this,SLOT(showInputDlg()));
    connect(MsgBtn,SIGNAL(clicked()),this,SLOT(showMsgDlg()));
    connect(CustomBtn,SIGNAL(clicked()),this,SLOT(showCustomDlg()));






}

Dialog::~Dialog()
{
}

void Dialog::showFile()
{
    //获取文件绝对路径+文件名，*.x后缀是所添加文件格式筛选，可点击选择多个后缀中的任意一种格式类型，与括号无关
    QString s = QFileDialog::getOpenFileName(this,"open file dialog,打开文件对话框","/","C++ files(*.cpp)\nC files(*.c)\nHead files *.h");
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

void Dialog::showInputDlg()
{
    inputDlg=new InputDlg(this);
    inputDlg->show();

}

void Dialog::showMsgDlg()
{
    msgDlg=new MsgBoxDlg();
    msgDlg->show();
}

void Dialog::showCustomDlg()
{
    label->setText(tr("Custom Message Box"));

    QMessageBox customMsgBox;
    customMsgBox.setWindowTitle(tr("用户自定义消息框"));

    QPushButton *yesBtn=customMsgBox.addButton(tr("yes"),QMessageBox::ActionRole);
    QPushButton *noBtn=customMsgBox.addButton(tr("No"),QMessageBox::ActionRole);
    QPushButton *cancelBtn=customMsgBox.addButton(QMessageBox::Cancel);

    customMsgBox.setText(tr("这是一个用户自定义消息框！"));
    //QPainter painter(this);
    //QPixmap pix;
    //pix.load("bilibili.png");
    //painter.drawPixmap(0,0,20,20,pix);

    customMsgBox.setIconPixmap(QPixmap("1.png"));
    //customMsgBox.setIconPixmap(pix);
    customMsgBox.exec();

    if(customMsgBox.clickedButton()==yesBtn)
        label->setText("Custom Message Box/Yes");
    if(customMsgBox.clickedButton()==noBtn)
        label->setText("Custom Messaage Box/No");
    if(customMsgBox.clickedButton()==cancelBtn)
        label->setText("Custom Message Box/Cancel");
    return;


}
