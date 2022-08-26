#ifndef MSGBOXDLG_H
#define MSGBOXDLG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>

class MsgBoxDlg : public QDialog
{
    Q_OBJECT
public:
    MsgBoxDlg(QWidget *parent=0);

private slots:
    void showQuestionMsg();
    void showInformationMsg();
    void showWarningMsg();
    void showCriticalMsg();
    void showAboutMsg();
    void showAboutQtMsg();

private:
    QLabel *label;
    QPushButton *questionBtn,*informationBtn,*warningBtn,*criticalBtn,*aboutBtn,*aboutQtBtn;
    QGridLayout *mainLayout;
};

#endif // MSGBOXDLG_H
