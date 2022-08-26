#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stringdialog.h"

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

void MainWindow::showString(QVariant str)
{
   //ui->stringLabel->setText(str);
    ui->stringLabel->setText(str.toString());
}


void MainWindow::on_pushButton_openSendWindow_clicked()
{
    StringDialog* dlg=new StringDialog(this);

    //连接信号槽函数
    connect(dlg,&StringDialog::stringExchange,[=](QString str){
        if(str=="qt"){
            //ui->stringLabel->setText("hello qt!");
            showString("hello qt !");
        }else{
            //ui->stringLabel->setText("error!");
            showString("error");
        }
    });

    dlg->move(760,200);
    dlg->show();

}

