#include "widget.h"
#include <iostream>
#include<string>
#include<map>
#include<vector>
#include<QtSql>
#include <QMessageBox>
#include <QDebug>
#include<QSqlError>
#include <stdlib.h>
using namespace std;
#include <QApplication>
#pragma execution_character_set("utf-8")
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server

bool OpenDatabase()
{

    qDebug()<<"ODBC driver?"<<db.isValid();
    QString dsn = QString::fromLocal8Bit("testdsn");    //数据源名称
    db.setHostName("localhost");                        //选择本地主机，127.0.1.1
    db.setDatabaseName(dsn);                            //设置数据源名称
    db.setUserName("sa");                               //登录用户
    db.setPassword("hxg1999323");                       //密码
    if(!db.open())                                      //打开数据库
    {
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0, QObject::tr("Database error"), db.lastError().text());
        return false;                                   //打开失败
    }
    else
        qDebug()<<"database open success!";
    return true;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    if(!OpenDatabase())
            return 1;
    QSqlQuery qry;
    QString sql="select * from Admin where ID='740453447'and pwd='hxg1999323'";
    if(qry.exec(sql))
    {
        if(qry.next())
            qDebug()<<"登陆成功";
        else
            qDebug()<<"database open success!";
    }

    else
    {
        qDebug()<<db.lastError().text();
    }
    w.show();
    return a.exec();
}
