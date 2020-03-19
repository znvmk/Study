#include "mywidget.h"
#include "ui_mywidget.h"
#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
#include <QApplication>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    setMinimumSize(200,12);
    setMaximumSize(200,120);

    QPushButton *quit=new QPushButton("Quit",this);
    quit->setGeometry(62,40,75,30);
    quit->setFont(QFont("Times",18,QFont::Bold));

    connect(quit,SIGNAL(clicked()),SLOT(quit()));
}

MyWidget::~MyWidget()
{
    delete ui;
}
void MyWidget::quit()
{
    QApplication* app;
    app->quit();
}
