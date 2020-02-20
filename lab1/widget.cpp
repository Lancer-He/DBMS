#include "widget.h"
#include "ui_widget.h"
#include<QtSql>
#include <QMessageBox>
#include <QDebug>
#include<QSqlError>
#include"adlog.h"
#include"searchlog.h"
#include"adrights.h"
#pragma execution_character_set("utf-8")
QString id;
QString pwd;

extern QSqlDatabase db;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}



void Widget::on_lineEdit_textEdited(const QString &arg1)
{
    id=arg1;
}

void Widget::on_lineEdit_2_textEdited(const QString &arg1)
{
    pwd=arg1;
}

void Widget::on_pushButton_clicked()
{
    int flag=0;
    QSqlQuery qry;
    QString sql="select * from Admin where ID='"+id+"'"+"and pwd='"+pwd+"'";
    if(qry.exec(sql)){
        if(qry.next()){
            ui->label_4->clear();
            ui->label_4->setText("登陆成功");
            flag=1;
        }
        else{
            ui->label_4->clear();
            ui->label_4->setText("账号或密码错误");
        }

    }
    else{
        qDebug()<<db.lastError().text();
    }
    if(flag)
    {
        this->hide();
        Adrights a;
        a.exec();
    }
}



void Widget::on_pushButton_2_clicked()
{

    ADlog l;
    l.exec();
}

void Widget::on_pushButton_3_clicked()
{
    int flag=0;
    QSqlQuery qry;
    QString sql="select * from Visitor where ID='"+id+"'"+"and pwd='"+pwd+"'";
    if(qry.exec(sql))
    {
        if(qry.next())
        {
            ui->label_4->clear();
            ui->label_4->setText("登陆成功");
            flag=1;

        }
        else
        {
            ui->label_4->clear();
            ui->label_4->setText("账号或密码错误");
        }

    }
    else
    {
        qDebug()<<db.lastError().text();
    }
    if(flag){
        this->hide();
        searchlog s;
        s.exec();
    }

}
