#ifndef INPUTDLG_H
#define INPUTDLG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>


class InputDlg : public QDialog
{
     Q_OBJECT

public:
    //InputDlg();
    //InputDlg(QWidget *parent=0);
     InputDlg(QWidget *parent = nullptr);
     ~InputDlg();

private:
    QLabel *nameLabel1,*sexLabel1,*ageLabel1,*scoreLabel1;
    QLabel *nameLabel2,*sexLabel2,*ageLabel2,*scoreLabel2;
    QPushButton *nameBtn,*sexBtn,*ageBtn,*scoreBtn;
    QGridLayout *mainLayout;




private slots:
    void ChangeName();
    void ChangeSex();
    void ChangeAge();
    void ChangeScore();
};

#endif // INPUTDLG_H
