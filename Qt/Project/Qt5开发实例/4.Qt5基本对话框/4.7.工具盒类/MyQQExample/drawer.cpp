#include "drawer.h"
#include <QGroupBox>
#include <QVBoxLayout>

Drawer::Drawer(QWidget *parent,Qt::WindowFlags f)
        :QToolBox(parent,f)
{
    setWindowTitle(tr("My QQ"));

    toolBtn1_1=new QToolButton;
    toolBtn1_1->setText(tr("张三"));
    toolBtn1_1->setIcon(QPixmap(":/res/11.jpg"));
    //toolBtn1_1->setIconSize(QPixmap(":/rew/11.jpg").size());
    toolBtn1_1->setIconSize(QSize(50,50));
    toolBtn1_1->setAutoRaise(true);
    toolBtn1_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_2=new QToolButton;
    toolBtn1_2->setText(tr("小孙"));
    toolBtn1_2->setIcon(QPixmap(":/res/15.jpg"));
    toolBtn1_2->setIconSize(QSize(50,50));
    toolBtn1_2->setAutoRaise(true);
    toolBtn1_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_3=new QToolButton;
    toolBtn1_3->setText(tr("李四"));
    toolBtn1_3->setIcon(QPixmap(":/res/12.jpg"));
    toolBtn1_3->setIconSize(QSize(50,50));
    toolBtn1_3->setAutoRaise(true);
    toolBtn1_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_4=new QToolButton;
    toolBtn1_4->setText(tr("王五"));
    toolBtn1_4->setIcon(QPixmap(":/res/13.jpg"));
    toolBtn1_4->setIconSize(QSize(50,50));
    toolBtn1_4->setAutoRaise(true);
    toolBtn1_4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_5=new QToolButton;
    toolBtn1_5->setText(tr("小赵"));
    toolBtn1_5->setIcon(QPixmap(":/res/14.jpg"));
    toolBtn1_5->setIconSize(QSize(50,50));
    toolBtn1_5->setAutoRaise(true);
    toolBtn1_5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);



    QGroupBox *groupBox1=new QGroupBox;
    QVBoxLayout *layout1=new QVBoxLayout(groupBox1);
    layout1->setAlignment(Qt::AlignHCenter);
    layout1->addWidget(toolBtn1_1);
    layout1->addWidget(toolBtn1_2);
    layout1->addWidget(toolBtn1_3);
    layout1->addWidget(toolBtn1_4);
    layout1->addWidget(toolBtn1_5);
    layout1->addStretch();

    toolBtn2_1=new QToolButton;
    toolBtn2_1->setText(tr("小王"));
    toolBtn2_1->setIcon(QPixmap(":/res/21.jpg"));
    toolBtn2_1->setIconSize(QSize(50,50));
    toolBtn2_1->setAutoRaise(true);
    toolBtn2_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn2_2=new QToolButton;
    toolBtn2_2->setText(tr("小张"));
    toolBtn2_2->setIcon(QPixmap(":/res/22.jpg"));
    toolBtn2_2->setIconSize(QSize(50,50));
    toolBtn2_2->setAutoRaise(true);
    toolBtn2_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QGroupBox *groupBox2=new QGroupBox;
    QVBoxLayout *layout2=new QVBoxLayout(groupBox2);
    layout1->setAlignment(Qt::AlignHCenter);
    layout1->addWidget(toolBtn2_1);
    layout1->addWidget(toolBtn2_2);

    toolBtn3_1=new QToolButton;
    toolBtn3_1->setText(tr("小陈"));
    toolBtn3_1->setIcon(QPixmap(":/res/31.jpg"));
    toolBtn3_1->setIconSize(QSize(50,50));
    toolBtn3_1->setAutoRaise(true);
    toolBtn3_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn3_2=new QToolButton;
    toolBtn3_2->setText(tr("小张"));
    toolBtn3_2->setIcon(QPixmap(":/res/22.jpg"));
    toolBtn3_2->setIconSize(QSize(50,50));
    toolBtn3_2->setAutoRaise(true);
    toolBtn3_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QGroupBox *groupBox3=new QGroupBox;
    QVBoxLayout *layout3=new QVBoxLayout(groupBox3);
    layout1->setAlignment(Qt::AlignHCenter);
    layout1->addWidget(toolBtn3_1);
    layout1->addWidget(toolBtn3_2);

    this->addItem((QWidget *)groupBox1,tr("我的好友"));
    this->addItem((QWidget *)groupBox2,tr("陌生人"));
    this->addItem((QWidget *)groupBox3,tr("黑名单"));

}
