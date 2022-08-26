﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTextEdit"
#include "QDockWidget"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("DockWindos"));//设置主窗口的标题栏文字
    QTextEdit* te=new QTextEdit(this);//定义一个QTextEdit对象作为主窗口
    te->setText(tr("Main Window"));
    te->setAlignment(Qt::AlignCenter);
    setCentralWidget(te);//将此编辑框设为主窗口中央窗体

    //停靠窗口1
    QDockWidget* dock=new QDockWidget(tr("DockWindow1"),this);
    dock->setFeatures(QDockWidget::DockWidgetMovable);//可移动
    dock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    QTextEdit* te1=new QTextEdit();
    te1->setText(tr("Windwo1,The dock widget can be moved between docks by the user" ""));
    dock->setWidget(te1);
    addDockWidget(Qt::RightDockWidgetArea,dock);

    //停靠窗口2
    dock =new QDockWidget(tr("DockWindow2"),this);
    dock->setFeatures(QDockWidget::DockWidgetClosable|QDockWidget::DockWidgetFloatable);//可关闭、可浮动
    QTextEdit* te2=new QTextEdit();
    te2->setText(tr("Window2,The dock widget can be detached from the main window,""and floated as an independent window,and can be closed."));
    dock->setWidget(te2);
    addDockWidget(Qt::RightDockWidgetArea,dock);

    //停靠窗口3
    dock =new QDockWidget(tr("DockWindow3"),this);
    dock->setFeatures(QDockWidget::DockWidgetFeatures());//全部特性
    QTextEdit* te3=new QTextEdit();
    te3->setText(tr("Window3,The dock widget can be closed,moved,and floated."));
    dock->setWidget(te3);
    addDockWidget(Qt::RightDockWidgetArea,dock);

}

MainWindow::~MainWindow()
{
    delete ui;
}

