#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QFrame>

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
    QPushButton* fileBtn;
    QLineEdit* fileLineEdit;
    QGridLayout* mainLayout;

    QPushButton* colorBtn;
    QFrame* colorFrame;

    QPushButton* fontBtn;
    QLineEdit* fontLineEdit;

private slots:
    void showFile();
    void showColor();
    void showFont();
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
