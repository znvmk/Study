#include "stackdlg.h"
#include "ui_stackdlg.h"
#include "QHBoxLayout"

StackDlg::StackDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StackDlg)
{
    ui->setupUi(this);


    setWindowTitle(tr("StackedWidget"));
    list=new QListWidget(this);
    list->insertItem(0,tr("Windwos1"));
    list->insertItem(0,tr("Windwos2"));
    list->insertItem(0,tr("Windwos3"));

    label1=new QLabel(tr("WindwoTest1"));
    label2=new QLabel(tr("WindwoTest2"));
    label2=new QLabel(tr("WindwoTest3"));

    stack=new QStackedWidget(this);
    stack->addWidget(label1);
    stack->addWidget(label2);
    stack->addWidget(label3);
    QHBoxLayout* mainLayout=new QHBoxLayout(this);
    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);
    mainLayout->addWidget(list);
    mainLayout->addWidget(stack,0,Qt::AlignHCenter);
    mainLayout->setStretchFactor(list,1);
    mainLayout->setStretchFactor(stack,3);
//    connect(list ,SIGNAL(currentRowChanged(int)),stack,SLOT(setCurrent Index(int)));


}

StackDlg::~StackDlg()
{
    delete ui;
}
