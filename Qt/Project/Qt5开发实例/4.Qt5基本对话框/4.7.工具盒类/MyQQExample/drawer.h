#ifndef DRAWER_H
#define DRAWER_H

#include <QToolBox>
#include <QToolButton>

class Drawer : public QToolBox
{
    Q_OBJECT

public:
    Drawer(QWidget *parent=Q_NULLPTR,Qt::WindowFlags f = Qt::WindowFlags());

private:
    QToolButton *toolBtn1_1,*toolBtn1_2,*toolBtn1_3,*toolBtn1_4,*toolBtn1_5;
    QToolButton *toolBtn2_1,*toolBtn2_2,*toolBtn3_1,*toolBtn3_2;



};

#endif // DRAWER_H
