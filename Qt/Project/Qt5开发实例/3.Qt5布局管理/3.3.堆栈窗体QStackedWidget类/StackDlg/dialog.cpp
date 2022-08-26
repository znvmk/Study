﻿#include "dialog.h"
#include "ui_dialog.h"
#include <QHBoxLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("StackedWidget"));

    list=new QListWidget(this);
    list->insertItem(0,tr("Window1"));
    list->insertItem(1,tr("Window2"));
    list->insertItem(1,tr("Window3"));

    label1=new QLabel(tr("WindowTest1"));
    label1=new QLabel(tr("WindowTest2"));
    label1=new QLabel(tr("WindowTest3"));

    stack=new QStackedWidget(this);
    stack->addWidget(label1);
    stack->addWidget(label2);
    stack->addWidget(label3);

    QHBoxLayout* mainLayout=new QHBoxLayout(this);
    //mainLayout->setMargin(5);
    mainLayout->setSpacing(5);
    mainLayout->addWidget(list);
    mainLayout->addWidget(stack,0,Qt::AlignHCenter);
    mainLayout->setStretchFactor(list,1);
    mainLayout->setStretchFactor(stack,3);
    connect(list,SIGNAL(currentRowChanged(int)),stack,SLOT(setCurrent Index(int)));

}

Dialog::~Dialog()
{
    delete ui;
}

