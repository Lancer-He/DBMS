#pragma execution_character_set("utf-8")

#include "searchlog.h"
#include "ui_searchlog.h"
#include<QtSql>
#include <QMessageBox>
#include <QDebug>
#include<QSqlError>
#include"details.h"
extern QSqlDatabase db;
extern QString detail_inf;


searchlog::searchlog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchlog)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

searchlog::~searchlog()
{
    delete ui;
}

void searchlog::on_pushButton_clicked()
{
    if(ui->radioButton->isChecked())
    {
        QString room=ui->lineEdit->text();
        QSqlQuery qry;
        QString sel="select *from Laboratory where room='"+room+"'";
        if(qry.exec(sel))
        {
            if(!qry.next())
            {
                QString title="warning";
                QString info="无当前实验室信息";
                QMessageBox::warning(this,title,info,QMessageBox::Ok,QMessageBox::NoButton);
            }
            else
            {
                QSqlQueryModel *model4= new QSqlTableModel(ui->tableView);;
                model4->setQuery(sel,db);
                model4->setHeaderData(0,Qt::Horizontal,QObject::tr("教室"));
                model4->setHeaderData(1,Qt::Horizontal,QObject::tr("电脑数量"));
                model4->setHeaderData(2,Qt::Horizontal,QObject::tr("示波器数量"));
                model4->setHeaderData(3,Qt::Horizontal,QObject::tr("实验箱数量"));
                model4->setHeaderData(4,Qt::Horizontal,QObject::tr("可容纳人数"));
                ui->tableView->setModel(model4);
            }
        }
    }
    if(ui->radioButton_2->isChecked())
    {
        bool flag=false;
        QString sel="select * from Laboratory";
        if(ui->checkBox->isChecked())
        {
            QString mincom=ui->spinBox->text();
            sel+=" where numofcom >="+mincom;
            flag=true;
        }
        if(ui->checkBox_2->isChecked())
        {
            QString minosc=ui->spinBox_2->text();
            if(flag==false)
            {
                sel+=" where numofosc >="+minosc;
                flag=true;
            }
            else
                sel+=" and numofosc >= "+minosc;
        }
        if(ui->checkBox_3->isChecked())
        {
            QString mincha=ui->spinBox_3->text();
            if(!flag)
            {
                sel+=" where numofcha >="+mincha;
                flag=true;
            }
            else
                sel+=" and numofcha >= "+mincha;
        }
        if(ui->checkBox_4->isChecked())
        {
            QString mincap=ui->spinBox_4->text();
            if(!flag)
            {
                sel+=" where capacity >="+mincap;
                flag=true;
            }
            else
                sel+=" and capacity >= "+mincap;
        }
        QSqlQuery qry;
        if(qry.exec(sel))
        {
            if(!qry.next())
            {
                QString title="error";
                QString info="无符合条件的实验室信息";
                QMessageBox::critical(this,title,info,QMessageBox::Ok,QMessageBox::NoButton);
            }
            else
            {
                qDebug()<<sel;
                QSqlQueryModel *model4= new QSqlTableModel(ui->tableView);
                model4->setQuery(sel,db);
                model4->setHeaderData(0,Qt::Horizontal,QObject::tr("教室"));
                model4->setHeaderData(1,Qt::Horizontal,QObject::tr("电脑数量"));
                model4->setHeaderData(2,Qt::Horizontal,QObject::tr("示波器数量"));
                model4->setHeaderData(3,Qt::Horizontal,QObject::tr("实验箱数量"));
                model4->setHeaderData(4,Qt::Horizontal,QObject::tr("可容纳人数"));
                ui->tableView->setModel(model4);
            }
        }
    }
}

void searchlog::on_tableView_doubleClicked(const QModelIndex &index)
{
    QAbstractItemModel *Imodel=ui->tableView->model();
    QModelIndex Iindex = Imodel->index(index.row(),0);  //index.row()为算选择的行号。1为所选中行的第一列。。
    QVariant datatemp=Imodel->data(Iindex);
    QString name=Imodel->data(index).toString();        //name即为所选择行的第一列的值
    qDebug()<<name<<datatemp.toString()<<index.column();
    if(index.column()==1)
    {
        if(name!="0")
        {
            QString room=datatemp.toString();
            detail_inf="select *from Computer where address='"+room+"'";
            details d;
            d.exec();
        }
    }
    else if(index.column()==2)
    {
        if(name!="0")
        {
            QString room=datatemp.toString();
            detail_inf="select *from Oscilloscope where address='"+room+"'";
            details d2;
            d2.exec();
        }
    }
}
