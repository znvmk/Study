#include "shapewidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>

ShapeWidget::ShapeWidget(QWidget *parent)
    : QWidget(parent)
{
      QPixmap pix;
      pix.load(":/1.jpg",0,Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither);
      resize(pix.size());
      setMask(QBitmap(pix.mask()));

}

ShapeWidget::~ShapeWidget()
{
}

void ShapeWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        dragPosition=event->globalPosition().toPoint()-frameGeometry().topLeft();
        event->accept();
    }
    if(event->button()==Qt::RightButton)
    {
        close();
    }
}
void ShapeWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->button()&Qt::LeftButton)
    {
        move(event->globalPosition().toPoint()-dragPosition);
        event->accept();
    }
}
void ShapeWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/1.jpg"));

}
//将图片资源从导入资源，构建后再图片放入运行debug目录
