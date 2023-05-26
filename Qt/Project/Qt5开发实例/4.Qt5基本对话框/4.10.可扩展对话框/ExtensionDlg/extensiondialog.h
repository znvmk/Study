#ifndef EXTENSIONDIALOG_H
#define EXTENSIONDIALOG_H

#include <QDialog>

class ExtensionDialog : public QDialog
{
    Q_OBJECT

public:
    ExtensionDialog(QWidget *parent = nullptr);
    ~ExtensionDialog();

private slots:
    void showDetailInfo();
private:
    void createBaseInfo();	//实现基本对话框窗体部分
    void createDetailInfo();	//实现扩展窗体部分
    QWidget *baseWidget;	//基本对话框窗体部分
    QWidget *detailWidget;	//扩展窗体部分

};

#endif // EXTENSIONDIALOG_H
