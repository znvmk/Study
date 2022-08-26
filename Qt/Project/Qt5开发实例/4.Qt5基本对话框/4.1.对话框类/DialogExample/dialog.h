#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QFrame>

#include "inputdlg.h"
#include "msgboxdlg.h"
#include "customdlg.h"

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    QPushButton *fileBtn,*colorBtn,*fontBtn;
    QLineEdit *fileLineEdit,*fontLineEdit;
    QGridLayout *mainLayout;
    QFrame * colorFrame;

    QPushButton *inputBtn,*MsgBtn,*CustomBtn;
    QLabel *label;
    InputDlg *inputDlg;
    MsgBoxDlg *msgDlg;

private slots:
    void showFile();
    void showColor();
    void showFont();
    void showInputDlg();
    void showMsgDlg();
    void showCustomDlg();



};
#endif // DIALOG_H
