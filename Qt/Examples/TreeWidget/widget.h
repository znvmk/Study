#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

public:
    void init();
    void updateParentItem(QTreeWidgetItem* item);

public slots:
    void treeItemChanged(QTreeWidgetItem* item,int column);

};

#endif // WIDGET_H
