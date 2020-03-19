#include "detail.h"


Detail::Detail(QWidget *parent) : QWidget(parent)
{

    NationalLabel=new QLabel(QString::fromLocal8Bit("国家/地址："));
    NationalComboBox=new QComboBox();
    NationalComboBox->insertItem(0,QString::fromLocal8Bit("中国"));
    NationalComboBox->insertItem(1,QString::fromLocal8Bit("美国"));
    NationalComboBox->insertItem(2,QString::fromLocal8Bit("英国"));

    ProvinceLabel=new QLabel(QString::fromLocal8Bit("省份："));
    ProvinceComboBox=new QComboBox();
    ProvinceComboBox->insertItem(0,QString::fromLocal8Bit("江苏省"));
    ProvinceComboBox->insertItem(0,QString::fromLocal8Bit("山东省"));
    ProvinceComboBox->insertItem(0,QString::fromLocal8Bit("浙江省"));

    CityLabel=new QLabel(QString::fromLocal8Bit("城市："));
    CityLineEdit=new QLineEdit();

    IntroductLabel=new QLabel(QString::fromLocal8Bit("个人说明："));
    IntroductTextEdit=new QTextEdit();

    MainLayout=new QGridLayout(this);
    MainLayout->setMargin(15);
    MainLayout->setSpacing(10);
    MainLayout->addWidget(NationalLabel,0,0);
    MainLayout->addWidget(NationalComboBox,0,1);
    MainLayout->addWidget(ProvinceLabel,1,0);
    MainLayout->addWidget(ProvinceComboBox,1,1);
    MainLayout->addWidget(CityLabel,2,0);
    MainLayout->addWidget(CityLineEdit,2,1);
    MainLayout->addWidget(IntroductLabel,3,0);
    MainLayout->addWidget(IntroductTextEdit,3,1);

}
