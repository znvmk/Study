#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
#include <QDockWidget>
//#include "main.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //停靠窗口
    QDockWidget* dock=new QDockWidget(QObject::tr("Dock Widget"),this);
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    //可移动
    dock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    QTextEdit* textDock=new QTextEdit();
    textDock->setText(QObject::tr("Window Dock,the dock widget van be moved between dockes by the user "));
    dock->setWidget(textDock);
    addDockWidget(Qt::LeftDockWidgetArea,dock);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
