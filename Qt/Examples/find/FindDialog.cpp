#include "FindDialog.h"
#include <QtGui>
#include <QtWidgets>
#include <QLabel>
#include <QLineEdit>

FindDialog::FindDialog(QWidget *parent)
    :QDialog(parent)
{
    label=new QLabel(tr("Find &what:"));
    lineEdit=new QLineEdit;
    label->setBuddy(lineEdit);

    caseCheckBox=new QCheckBox(tr("Match &case"));
    backwardCheckBox=new QCheckBox(tr("Search &back")) ;

    findButton=new QPushButton(tr("&Find"));
    findButton->setDefault(true);
    findButton->setEnabled(false);

    closeButton=new QPushButton(tr("&Find"));
    findButton->setDefault(true);
    findButton->setEnabled(false);

    closeButton=new QPushButton(tr("Close"));

    connect(lineEdit,SIGNAL(textChanged(const QString &)),this,SOLT(enableFindButton(const QString &)));
    connect(findButton,SIGNAL(clicked()),this,SLOT(findClicked()));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));

    QHBoxLayout *topLeftLayout=new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    QVBoxLayout *leftLayout=new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);

    QVBoxLayout *rightLayout=new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    QHBoxLayout *mainLayout= new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    /*创建水平排列控件，并将leftLayout和rightLayout两个布局控件添加到mainLayout布局中*/

    setLayout(mainLayout);//设置主窗体的布局为mainLayout
    setWindowTitle(tr("Find"));//设置主窗体的标题
    setFixedHeight(sizeHint().height());//设置窗体的高度
    }
    void FindDialog::findClicked()//实现响应函数
    {
        QString text = lineEdit->text();//取得文本框中的内容

        Qt::CaseSensitivity cs = caseCheckBox->isChecked()?Qt::CaseSensitive:Qt::CaseInsensitive;
        if(backwardCheckBox->isChecked()){
            emit findPrevious(text,cs);//emit也是个宏
        }else{
            emit findNext(text,cs);
        }
        /*根据backwardCheckBox状态发出findPrevious或者findNext信号执行*/
    }
    void FindDialog::enableFindButton(const QString &text){//响应函数，如果用户改变文本框内容，调用该函数
         findButton->setEnabled(!text.isEmpty());//设置find()按钮可用


}
