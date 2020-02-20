#include "adlog.h"
#include "ui_adlog.h"
#include<QtSql>
#include <QMessageBox>
#include <QDebug>
#include<QSqlError>
#pragma execution_character_set("utf-8")
QString logid;
QString logpwd;
QString logpwd2;
extern QSqlDatabase db;

ADlog::ADlog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ADlog)
{
    ui->setupUi(this);
}

ADlog::~ADlog()
{
    delete ui;
}

void ADlog::on_lineEdit_textEdited(const QString &arg1)
{
    logid=arg1;
}

void ADlog::on_lineEdit_3_textEdited(const QString &arg1)
{
    logpwd=arg1;
}

void ADlog::on_lineEdit_2_textEdited(const QString &arg1)
{
    logpwd2=arg1;
}

void ADlog::on_pushButton_clicked()
{
    ui->label_5->clear();
    QSqlQuery qry;
    QString sql="select * from Visitor where ID='"+logid+"'";
    if(qry.exec(sql)){
        if(qry.next()){

            ui->label_5->setText("用户名已存在");
        }
        else{
            if(logpwd!=logpwd2){
                ui->label_5->setText("两次密码输入不同，请重新输入");
                ui->lineEdit_2->clear();
                ui->lineEdit_3->clear();
            }
            else{
                QSqlQuery sign;
                QString signsql="insert Visitor values ('"+logid+"','"+logpwd+"')";
                if(sign.exec(signsql)){
                    ui->label_5->setText("注册成功");
                }
                else{
                    qDebug()<<db.lastError().text();
                }
            }
        }
    }
    else
    {
        qDebug()<<db.lastError().text();
    }
}
