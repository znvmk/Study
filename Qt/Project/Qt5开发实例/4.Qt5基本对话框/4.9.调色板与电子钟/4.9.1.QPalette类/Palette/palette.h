#ifndef PALETTE_H
#define PALETTE_H

#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>

class Palette : public QDialog
{
    Q_OBJECT

public:
    Palette(QWidget *parent = nullptr);
    ~Palette();

public:
   void createCtrlFrame();            //完成窗体左半部分颜色选择区的创建
   void createContentFrame();         //完成窗体右半部分的创建
   void fillColorList(QComboBox *);   //完成向颜色下拉列表框中插入颜色的工作

private slots:
   void ShowWindow();
   void ShowWindowText();
   void ShowButton();
   void ShowButtonText();
   void ShowBase();

private:
   QFrame *ctrlFrame,*contentFrame;   //显示选择面板，具体显示面板
   QComboBox *windowComboBox,*windowTextComboBox,*buttonComboBox,*buttonTextComboBox,*baseComboBox;
   QLabel *windowLabel,*windowTextLabel,*buttonLabel,*buttonTextLabel,*baseLabel;
   QLabel *label1,*label2;
   QComboBox *comboBox1;
   QLineEdit *lineEdit2;
   QTextEdit *textEdit;
   QPushButton *OkBtn,*CancelBtn;

};
#endif // PALETTE_H
