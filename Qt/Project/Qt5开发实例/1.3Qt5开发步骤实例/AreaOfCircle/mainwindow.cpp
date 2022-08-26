#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtMath"
#include <iostream>
#include <string>

const static double PI=3.141593589793238;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   double dRadius=ui->lineEdit_Radius->text().toFloat();
   double dArea=dRadius*dRadius*PI;
   //使用string转换
   std::string s=std::to_string(dArea);
   //使用QString转换
   //QString sArea=QString("%1").arg(dArea);
   //QString::number(数据，进制，小数位数);
   QString s1Area=QString::number(dArea,10,10);
   ui->lineEdit_Area->setText(s1Area);

}

