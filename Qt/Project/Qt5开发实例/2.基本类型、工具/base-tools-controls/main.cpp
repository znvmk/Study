#include "mainwindow.h"

#include <QApplication>

#include <iostream>

#include <QtDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QString qstr1 = "Welcome ";
    qstr1 += "to you!";
    QString qstr2 = "Hello, ";
    qstr2 += "World!";

    QTextStream(stdout)<<"QTextStream test:\n";
    QTextStream(stdout)<<qstr1;
    QTextStream(stdout)<<"\n"<<qstr2<<"\n";

    std::string str1,str2;
    str1="iostream std::string test1";
    str2="test out 汉字测试 。。";
    std::cout<<str1<<std::endl;
    std::cout<<str2<<std::endl;

    qDebug()<<"QDebug output test.测试";
    QString strArg;
    strArg=QString("     %1 was born in %2.  ").arg("John").arg(1982);
    //移除两端的空白
    strArg=strArg.trimmed();

    QTextStream qin(stdin);
    QTextStream qout(stdout);
    qout.setEncoding(QStringConverter::System);
    qin.setEncoding(QStringConverter::System);
    qout<<qin.read(1);
    QTextStream(stdout)<< "arg()函数和字符串操作函数trimmed()移除两端空白：";
    QTextStream(stdout)<<"\n";
    QTextStream(stdout)<<strArg;
    //查询，startsWith()一...字符串开头，返回true,false
    //查询，contains（）是否包含某个字符串
    QString sResult;
   // sResult=QString::number(strArg.contains("born",Qt::CaseSensitive));
    if(strArg.contains("born",Qt::CaseSensitive))
            sResult="是";
     else
            sResult="否";
    QTextStream(stdout)<<"\n";
     QTextStream(stdout)<<"\""<<strArg<<"\" ";
    QTextStream(stdout)<<"是否包含 \"born\" :"<<sResult;
    QTextStream(stdout)<<"\n";


    //容器类
    QTextStream(stdout)<<"容器类\n";
    QList<QString> sList;
    QString sInsertList("This is a list insert test string");
    sList<<sInsertList;
    QTextStream(stdout)<<"list[0]:"<<sList[0]<<"\n list test.";
    QList<int>iList;
    iList<<1<<2<<3<<4<<5;
    QListIterator<int>iIterator(iList);
    QTextStream(stdout)<<"list 迭代器:"<<"\n";
    for(;iIterator.hasNext();)
        QTextStream(stdout)<<iIterator.next();


    return a.exec();

}
