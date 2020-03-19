#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("myfirsthello");
    setWindowIcon(QIcon("my.ico"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
