#ifndef STRINGDIALOG_H
#define STRINGDIALOG_H

#include <QDialog>

namespace Ui {
class StringDialog;
}

class StringDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StringDialog(QWidget *parent = nullptr);
    ~StringDialog();

private slots:
    void on_emitButton_clicked();

private:
    Ui::StringDialog *ui;

signals:
    //信号槽数据交换函数
    void stringExchange(QString str);
};

#endif // STRINGDIALOG_H
