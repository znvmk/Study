#ifndef BASEINFO_H
#define BASEINFO_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QImage>

class BaseInfo : public QWidget
{
    Q_OBJECT
public:
    explicit BaseInfo(QWidget *parent = nullptr);
private:
    QImage img;
private:
    //左侧
    QLabel* UserNameLabel;
    QLabel* NameLabel;
    QLabel* SexLabel;
    QLabel* DepartmentLabel;
    QLabel* AgeLabel;
    QLabel* OtherLabel;
    QLineEdit* UserNameLineEdit;
    QLineEdit* NameLineEdit;
    QComboBox* SexComboBox;
    QTextEdit* DepartmentTextEdit;
    QLineEdit* AgeLineEdit;
    QGridLayout* LeftLayout;

    //右侧
    QLabel* HeadLabel;
    QLabel* HeadIconLabel;
    QPushButton* UpdateHeadBtn;
    QHBoxLayout* TopRightLayout;
    QLabel* IntroductionLabel;
    QTextEdit* IntroductionTextEdit;
    QVBoxLayout* RightLayout;

    //底部
    QPushButton* OkBtn;
    QPushButton* CancelBtn;
    QHBoxLayout* BottomLayout;
signals:

public slots:
};

#endif // BASEINFO_H
