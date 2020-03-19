#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    QLabel *label1,*label2;
    QLineEdit *lineEdit;
    QPushButton *button;

private slots:
    void showArea();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
