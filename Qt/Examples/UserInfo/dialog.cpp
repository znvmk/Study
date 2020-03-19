//#pragma execution_chatcter_set("utf-8")
//#include <qtextcodec.h>

#include "dialog.h"
#include "ui_dialog.h"
#include <QPixmap>
#include <QPushButton>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);





    setWindowTitle(tr("UserInfo"));

    //左侧
//    UserNameLabel = new QLabel(tr("用户名："));
    UserNameLabel = new QLabel(QString::fromLocal8Bit("用户名："));

    UserNameLineEdit=new QLineEdit();
    NameLabel=new QLabel(QString::fromLocal8Bit("姓名："));
    NameLineEdit=new QLineEdit();
    SexLabel=new QLabel(QString::fromLocal8Bit("性别："));
    SexComboBox=new QComboBox();
    SexComboBox->addItem(QString::fromLocal8Bit("女"));
    SexComboBox->addItem(QString::fromLocal8Bit("男"));
    DepartmentLabel=new QLabel(QString::fromLocal8Bit("部门:"));
    DepartmentTextEdit=new QTextEdit();
    AgeLabel=new QLabel(QString::fromLocal8Bit("年龄："));
    AgeLineEdit=new QLineEdit();
    OtherLabel=new QLabel(QString::fromLocal8Bit("备注："));
    OtherLabel->setFrameStyle(QFrame::Panel|QFrame::Sunken);

    LeftLayout=new QGridLayout();
    LeftLayout->addWidget(UserNameLabel,0,0);
    LeftLayout->addWidget(UserNameLineEdit,0,1);

    LeftLayout->addWidget(NameLabel,1,0);
    LeftLayout->addWidget(NameLineEdit,1,1);

    LeftLayout->addWidget(SexLabel,2,0);
    LeftLayout->addWidget(SexComboBox,2,1);

    LeftLayout->addWidget(DepartmentLabel,3,0);
    LeftLayout->addWidget(DepartmentTextEdit,3,1);

    LeftLayout->addWidget(AgeLabel,4,0);
    LeftLayout->addWidget(AgeLineEdit,4,1);

    LeftLayout->addWidget(OtherLabel,5,0,1,2);

    LeftLayout->setColumnStretch(0,1);
    LeftLayout->setColumnStretch(1,3);

    //右侧
    HeadLabel=new QLabel(QString::fromLocal8Bit("头像："));
    HeadIconLabel=new QLabel();
//    QPixmap icon("E:\\znp\\GitHub\\Personal\\Study\\Qt\\Examples\\UserInfo\\1.png");
//    QPixmap icon("1.png");
      QPixmap icon;
//    icon.load("1.png");
      icon.load("E:\\znp\\GitHub\\Personal\\Study\\Qt\\Examples\\UserInfo\\1.png");
      HeadIconLabel->setPixmap(icon);
      HeadIconLabel->resize(icon.width(),icon.height());
  //  if(img.load(":/1.png"))

    {

       // HeadLabel->setPixmap(QPixmap::fromImage(img));

    }
   // img.load(":/1.png");
  //  HeadLabel->setPixmap(QPixmap::fromImage(img));
  //  HeadLabel->resize(img.width(),img.height());
    UpdateHeadBtn=new QPushButton(QString::fromLocal8Bit("更新"));

    TopRightLayout=new QHBoxLayout();
    TopRightLayout->setSpacing(20);
    TopRightLayout->addWidget(HeadLabel);
    TopRightLayout->addWidget(HeadIconLabel);
    TopRightLayout->addWidget(UpdateHeadBtn);

    IntroductionLabel=new QLabel(QString::fromLocal8Bit("个人说明："));
    introductionTextEdit=new QTextEdit;

    RightLayout=new QVBoxLayout();
    RightLayout->setMargin(10);
    RightLayout->addLayout(TopRightLayout);
    RightLayout->addWidget(introductionTextEdit);

    //底部
    OkBtn=new QPushButton(QString::fromLocal8Bit("确定"));
    CancelBtn=new QPushButton(QString::fromLocal8Bit("取消"));

    BottomLayout=new QHBoxLayout();
    BottomLayout->addStretch();
    BottomLayout->addWidget(OkBtn);
    BottomLayout->addWidget(CancelBtn);

    QGridLayout* mainLayout=new QGridLayout(this);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);
    mainLayout->addLayout(LeftLayout,0,0);
    mainLayout->addLayout(RightLayout,0,1);
    mainLayout->addLayout(BottomLayout,1,0,1,2);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);


}

Dialog::~Dialog()
{
    delete ui;
}
