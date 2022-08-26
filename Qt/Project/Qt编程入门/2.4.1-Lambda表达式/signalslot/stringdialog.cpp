#include "stringdialog.h"
#include "ui_stringdialog.h"

StringDialog::StringDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StringDialog)
{
    ui->setupUi(this);
}

StringDialog::~StringDialog()
{
    delete ui;
}

void StringDialog::on_emitButton_clicked()
{
    QString str=ui->stringLineEdit->text();
    //发送数据，emit：发射函数
    emit stringExchange(str);
}

