#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>

class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    ProgressDialog(QWidget *parent = nullptr);
    ~ProgressDialog();

private slots:
    void startProgress();

private:
    QLabel *FileNum,*ProgressType;
    QLineEdit *FileNumLineEdit;
    QComboBox *comboBox;
    QProgressBar *progressBar;
    QPushButton *starBtn;
    QGridLayout *mainLayout;


};
#endif // PROGRESSDIALOG_H
