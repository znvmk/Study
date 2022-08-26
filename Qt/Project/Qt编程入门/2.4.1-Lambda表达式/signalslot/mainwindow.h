#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_openSendWindow_clicked();

private:
    Ui::MainWindow *ui;

private:
    //获取信号槽数据并显示
   // void showString(QString str);
    void showString(QVariant str);
};
#endif // MAINWINDOW_H
