#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    //左侧
    QLabel* UserNameLabel;
    QLabel* NameLabel;
    QLabel* SexLabel;
    QLabel* DepartmentLabel;
    QLabel* AgeLabel;
    QLabel* OtherLabel;
    QLineEdit* UserNameLineEdit;
    QLineEdit* NameLineEdit;
    QLineEdit* AgeLineEdit;
    QComboBox* SexComboBox;
    QTextEdit* DepartmentTextEdit;
    QGridLayout* LeftLayout;

    //右侧
    QLabel* HeadLabel;//右上角部分
    QLabel* HeadIconLabel;
    QPushButton*UpdateHeadBtn;
    QHBoxLayout* TopRightLayout;

    QLabel* IntroductionLabel;
    QTextEdit* IntroductionTextEdit;
    QVBoxLayout* RightLayout;

    //底部
    QPushButton* OkBtn;
    QPushButton* CancelBtn;
    QHBoxLayout* BottomLayout;
};
#endif // DIALOG_H
