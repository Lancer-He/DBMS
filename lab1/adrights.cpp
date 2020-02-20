#include "adrights.h"
#include "ui_adrights.h"
#include<QtSql>
#include<QMessageBox>
#include <QMessageBox>
#include <QDebug>
#include<QSqlError>
#include <QSqlTableModel>
#include <QTableView>
#include"searchlog.h"
#include"details.h"
extern QSqlDatabase db;
#pragma execution_character_set("utf-8")


QString room,numofcom="0",numofosc="0",numofcha="0",capacity="0",cpu,os,ram,bandwidth;
QString numofcom2,numofosc2,numofcha2,capacity2,cpu2,os2,ram2,bandwidth2;
bool flagcom,flagcha,flagosc,flagcpu,flagos,flagram,flagbw,flagcap;
QSqlQueryModel *model3;
QSqlQueryModel *model;
QSqlQueryModel *model2;
QSqlQueryModel *model4;
QString detail_inf;

void setflag()
{
    flagbw=true;
    flagos=true;
    flagcha=true;
    flagcom=true;
    flagcpu=true;
    flagosc=true;
    flagram=true;
    flagcap=true;
}


Adrights::Adrights(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Adrights)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_5->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_6->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_5->setSelectionBehavior(QAbstractItemView::SelectRows);
    //初始化四个tableview
    model = new QSqlTableModel(ui->tableView);
    model->setQuery("select *from Laboratory ",db);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("教室"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("电脑数量"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("示波器数量"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("实验箱数量"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("可容纳人数"));
    ui->tableView->setModel(model);

    model2 = new QSqlTableModel(ui->tableView_2);
    model2->setQuery("select *from Laboratory ",db);
    model2->setHeaderData(0,Qt::Horizontal,QObject::tr("教室"));
    model2->setHeaderData(1,Qt::Horizontal,QObject::tr("电脑数量"));
    model2->setHeaderData(2,Qt::Horizontal,QObject::tr("示波器数量"));
    model2->setHeaderData(3,Qt::Horizontal,QObject::tr("实验箱数量"));
    model2->setHeaderData(4,Qt::Horizontal,QObject::tr("可容纳人数"));
    ui->tableView_2->setModel(model2);

    model3 = new QSqlTableModel(ui->tableView_5);
    model3->setQuery("select *from Laboratory ",db);
    model3->setHeaderData(0,Qt::Horizontal,QObject::tr("教室"));
    model3->setHeaderData(1,Qt::Horizontal,QObject::tr("电脑数量"));
    model3->setHeaderData(2,Qt::Horizontal,QObject::tr("示波器数量"));
    model3->setHeaderData(3,Qt::Horizontal,QObject::tr("实验箱数量"));
    model3->setHeaderData(4,Qt::Horizontal,QObject::tr("可容纳人数"));
    ui->tableView_5->setModel(model3);

    model4 = new QSqlTableModel(ui->tableView_6);
    model4->setHeaderData(0,Qt::Horizontal,QObject::tr("教室"));
    model4->setHeaderData(1,Qt::Horizontal,QObject::tr("电脑数量"));
    model4->setHeaderData(2,Qt::Horizontal,QObject::tr("示波器数量"));
    model4->setHeaderData(3,Qt::Horizontal,QObject::tr("实验箱数量"));
    model4->setHeaderData(4,Qt::Horizontal,QObject::tr("可容纳人数"));

}

Adrights::~Adrights()
{
    delete ui;
}


void Adrights::on_lineEdit_textEdited(const QString &arg1)
{
    room=arg1;
}

void Adrights::on_spinBox_valueChanged(const QString &arg1)
{
    numofcom=arg1;
}

void Adrights::on_spinBox_2_valueChanged(const QString &arg1)
{
    numofosc=arg1;
}

void Adrights::on_spinBox_4_valueChanged(const QString &arg1)
{
    numofcha=arg1;
}

void Adrights::on_spinBox_3_valueChanged(const QString &arg1)
{
    capacity=arg1;
}

void Adrights::on_lineEdit_2_textEdited(const QString &arg1)
{
    cpu=arg1;
}

void Adrights::on_lineEdit_3_textEdited(const QString &arg1)
{
    ram=arg1;
}

void Adrights::on_lineEdit_4_textEdited(const QString &arg1)
{
    os=arg1;
}

void Adrights::on_lineEdit_5_textEdited(const QString &arg1)
{
    bandwidth=arg1;
}

void Adrights::on_pushButton_clicked()
{
    QString insert="insert Laboratory values ('"+room+"',"+numofcom+","+numofosc+","+numofcha+","+capacity+
            ")";
    if(numofcom!="0")
    {
        insert+=" insert Computer values ('"+room+"','"+cpu+"','"+ram+"','"+os+"',"+numofcom+")";
    }
    if(numofosc!="0")
    {
        insert+=" insert Oscilloscope values('"+room+"','"+bandwidth+"',"+numofosc+")";
    }
    QString check="select *from Laboratory where room='"+room+"'";
    QSqlQuery qry;
    if(qry.exec(check))
    {
        if(qry.next())
        {
            QString title="warning";
            QString info="当前实验室信息已存在";
            QMessageBox::warning(this,title,info,QMessageBox::Ok,QMessageBox::NoButton);
        }
        else
        {
            if(qry.exec(insert))
            {

                QString title="success";
                QString info="添加成功";
                QMessageBox::information(this,title,info,QMessageBox::Ok,QMessageBox::NoButton);
            }
            else
            {
                QString title="error";
                QString info="添加失败";
                QMessageBox::critical(this,title,info,QMessageBox::Ok,QMessageBox::NoButton);
                qDebug()<<db.lastError().text();
            }
        }
    }
    else
    {
        qDebug()<<"步骤一查询失败！";
    }
    model->setQuery("select *from Laboratory ",db);
    model2->setQuery("select *from Laboratory ",db);
    model3->setQuery("select *from Laboratory ",db);

    ui->tableView->setModel(model);
    ui->tableView_2->setModel(model2);
    ui->tableView_5->setModel(model3);
}

void Adrights::on_pushButton_10_clicked()
{
    QSqlQueryModel *model = new QSqlTableModel(ui->tableView);
    model->setQuery("select *from Laboratory ",db);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("教室"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("电脑数量"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("示波器数量"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("实验箱数量"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("可容纳人数"));
    ui->tableView->setModel(model);
}

//修改界面点击选择
void Adrights::on_pushButton_2_clicked()
{
    QString room2=ui->lineEdit_6->text();
    QString check="select *from Laboratory where room='"+room2+"'";
    QSqlQuery qry;
    if(qry.exec(check))
    {
        if(qry.next())
        {
            ui->spinBox_5->setValue(qry.value(1).toInt());
            ui->spinBox_6->setValue(qry.value(2).toInt());
            ui->spinBox_7->setValue(qry.value(3).toInt());
            ui->spinBox_8->setValue(qry.value(4).toInt());
            if(qry.value(1).toInt()!=0)
            {
                    QString com="select *from Computer where address='"+room2+"'";
                    QSqlQuery qry2;
                    if(qry2.exec(com))
                    {
                        if(qry2.next())
                        {
                            ui->lineEdit_7->setText(qry2.value(1).toString());
                            ui->lineEdit_8->setText(qry2.value(2).toString());
                            ui->lineEdit_9->setText(qry2.value(3).toString());
                        }
                    }

            }
            else{
                ui->lineEdit_7->clear();
                ui->lineEdit_8->clear();
                ui->lineEdit_9->clear();
            }
            if(qry.value(2).toInt()!=0)
            {
                    QString osc="select *from Oscilloscope where address='"+room2+"'";
                    QSqlQuery qry2;
                    if(qry2.exec(osc))
                    {
                        if(qry2.next())
                        {
                            ui->lineEdit_10->setText(qry2.value(1).toString());
                        }
                    }

            }
            else{
                ui->lineEdit_10->clear();
            }
        }
        else{
            QString title="warning";
            QString info="无当前实验室信息";
            QMessageBox::warning(this,title,info,QMessageBox::Ok,QMessageBox::NoButton);
        }
    }
    QSqlQueryModel *model = new QSqlTableModel(ui->tableView_2);
    model->setQuery("select *from Laboratory ",db);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("教室"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("电脑数量"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("示波器数量"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("实验箱数量"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("可容纳人数"));
    ui->tableView_2->setModel(model);
    numofcom2=ui->spinBox_5->text();
    numofosc2=ui->spinBox_6->text();
    numofcha2=ui->spinBox_7->text();
    capacity2=ui->spinBox_8->text();
    cpu2=ui->lineEdit_7->text();
    ram2=ui->lineEdit_8->text();
    os2=ui->lineEdit_9->text();
    bandwidth2=ui->lineEdit_10->text();
}

//修改界面点击修改
void Adrights::on_pushButton_3_clicked()
{
    setflag();
    QSqlQuery qry;
    QString update;
    //电脑数量修改
    if(ui->spinBox_5->text()!=numofcom2){
        if(ui->spinBox_5->value()==0)
        {
            update="update Laboratory set numofcom=0 where room='" +ui->lineEdit_6->text()+"'";
            if(!qry.exec(update))
            {
                flagcom=false;
            }
            update="delete from Computer where address='"+ui->lineEdit_6->text()+"'";
            if(!qry.exec(update))
            {
                flagcom=false;
            }
        }
        else
        {
            if(numofcom2!="0")
            {
                update="update Laboratory set numofcom="+ui->spinBox_5->text()+"where room='" +ui->lineEdit_6->text()+"'";
                if(!qry.exec(update))
                {
                    flagcom=false;
                }
            }
            else
            {
                update="update Laboratory set numofcom="+ui->spinBox_5->text()+"where room='" +ui->lineEdit_6->text()+"'";
                update+="insert Computer values ('"+ui->lineEdit_6->text()+"','"+ui->lineEdit_7->text()+"','"+ui->lineEdit_8->text()+
                        "','"+ui->lineEdit_9->text()+"',"+ui->spinBox_5->text()+")";
                if(!qry.exec(update))
                {
                    flagcom=false;
                }
            }
        }
    }
    //示波器数量修改
    if(ui->spinBox_6->text()!=numofosc2){
        if(ui->spinBox_6->value()==0)
        {
            update="update Laboratory set numofosc=0 where room='" +ui->lineEdit_6->text()+"'";
            if(!qry.exec(update))
            {
                flagosc=false;
            }
            update="delete from Oscilloscope where address='"+ui->lineEdit_6->text()+"'";
            if(!qry.exec(update))
            {
                flagosc=false;
            }
        }
        else
        {
            if(numofosc2!="0")
            {
                update="update Laboratory set numofosc="+ui->spinBox_6->text()+"where room='" +ui->lineEdit_6->text()+"'";
                if(!qry.exec(update))
                {
                    flagosc=false;
                }
            }
            else
            {
                update="update Laboratory set numofosc="+ui->spinBox_6->text()+"where room='" +ui->lineEdit_6->text()+"'";
                update+="insert Oscilloscope values ('"+ui->lineEdit_6->text()+"','"+ui->lineEdit_10->text()+"',"+ui->spinBox_6->text()+")";
                if(!qry.exec(update))
                {
                    flagosc=false;
                }
            }

        }
    }
    //实验箱数量修改
    if(ui->spinBox_7->text()!=numofcha2){
        update="update Laboratory set numofcha="+ui->spinBox_7->text()+"where room='" +ui->lineEdit_6->text()+"'";
        if(!qry.exec(update))
        {
            flagcha=false;
        }
    }
    //容量修改
    if(ui->spinBox_8->text()!=capacity2){
        update="update Laboratory set capacity="+ui->spinBox_8->text()+"where room='" +ui->lineEdit_6->text()+"'";
        if(!qry.exec(update))
        {
            flagcap=false;
        }
    }
    //cpu修改
    if(ui->lineEdit_7->text()!=cpu2){
        if(ui->spinBox_5->value()!=0)
        {
            update="update Computer set cpu='"+ui->lineEdit_7->text()+"' where address='" +ui->lineEdit_6->text()+"'";
            if(!qry.exec(update))
            {
                flagcpu=false;
            }
        }
    }
    //ram修改
    if(ui->lineEdit_8->text()!=ram2){
        if(ui->spinBox_5->value()!=0)
        {
            update="update Computer set ram='"+ui->lineEdit_8->text()+"' where address='" +ui->lineEdit_6->text()+"'";
            if(!qry.exec(update))
            {
                flagram=false;
            }
        }
    }
    //os修改
    if(ui->lineEdit_9->text()!=os2){
        if(ui->spinBox_5->value()!=0)
        {
            update="update Computer set os='"+ui->lineEdit_9->text()+"' where address='" +ui->lineEdit_6->text()+"'";
            if(!qry.exec(update))
            {
                flagos=false;
            }
        }
    }
    //带宽修改
    if(ui->lineEdit_10->text()!=bandwidth2){
        if(ui->spinBox_6->value()!=0)
        {
            update="update Oscilloscope set bandwidth='"+ui->lineEdit_10->text()+"' where address='" +ui->lineEdit_6->text()+"'";
            if(!qry.exec(update))
            {
                flagbw=false;
            }
        }
    }
    if(!(flagcom&&flagcha&&flagosc&&flagcpu&&flagos&&flagram&&flagbw))
    {
        QString title="error";
        QString info="出现错误！";
        QMessageBox::critical(this,title,info,QMessageBox::Ok,QMessageBox::NoButton);
    }
    else
    {
        QString title="success";
        QString info="修改成功！";
        QMessageBox::information(this,title,info,QMessageBox::Ok,QMessageBox::NoButton);
    }
    model->setQuery("select *from Laboratory ",db);
    model2->setQuery("select *from Laboratory ",db);
    model3->setQuery("select *from Laboratory ",db);

    ui->tableView->setModel(model);
    ui->tableView_2->setModel(model2);
    ui->tableView_5->setModel(model3);



}

//删除按钮点击
void Adrights::on_pushButton_4_clicked()
{

    bool flag=true;
    int row=ui->tableView_5->currentIndex().row();
    qDebug()<<ui->tableView_5->currentIndex().row();
    QString delroom=model3->data(model3->index(row,0)).toString();
    QString dlgTitle="Question消息框";
    QString strInfo="确认删除 "+delroom+" 实验室信息吗？";
    QMessageBox::StandardButton  defaultBtn=QMessageBox::NoButton; //缺省按钮
    QMessageBox::StandardButton result;//返回选择的按钮
    result=QMessageBox::question(this, dlgTitle, strInfo,
                          QMessageBox::Yes|QMessageBox::No |QMessageBox::Cancel,
                          defaultBtn);
    if(result== QMessageBox::Yes)
    {
        QSqlQuery qry;
        QString sel="select *from Laboratory where room='"+delroom+"'";
        if(qry.exec(sel))
        {
            if(qry.next())
            {
                if(qry.value(1).toInt()!=0)
                {
                    QSqlQuery qry2;
                    QString del="delete from Computer where address='"+delroom+"'";
                    if(!qry2.exec(del))
                    {
                        flag=false;
                        QString title="error";
                        QString info="出现错误！";
                        QMessageBox::critical(this,title,info,QMessageBox::Ok,QMessageBox::NoButton);
                    }
                }
                if(qry.value(2).toInt()!=0)
                {
                    QSqlQuery qry2;
                    QString del="delete from Oscilloscope where address='"+delroom+"'";
                    if(!qry2.exec(del))
                    {
                        flag=false;
                        QString title="error";
                        QString info="出现错误！";
                        QMessageBox::critical(this,title,info,QMessageBox::Ok,QMessageBox::NoButton);
                    }
                }
                QSqlQuery qry2;
                QString del="delete from Laboratory where room='"+delroom+"'";
                if(!qry2.exec(del))
                {
                    flag=false;
                    QString title="error";
                    QString info="出现错误！";
                    QMessageBox::critical(this,title,info,QMessageBox::Ok,QMessageBox::NoButton);
                }
            }

        }
        else{
            flag=false;
        }
        if(flag)
        {
            QString title="success";
            QString info="删除成功！";
            QMessageBox::information(this,title,info,QMessageBox::Ok,QMessageBox::NoButton);
        }
    }

    model->setQuery("select *from Laboratory ",db);
    model2->setQuery("select *from Laboratory ",db);
    model3->setQuery("select *from Laboratory ",db);

    ui->tableView->setModel(model);
    ui->tableView_2->setModel(model2);
    ui->tableView_5->setModel(model3);
}

//更多查询
void Adrights::on_pushButton_11_clicked()
{
    searchlog s;
    s.exec();
}

void Adrights::on_pushButton_9_clicked()
{
    QString searchroom=ui->lineEdit_21->text();
    QSqlQuery qry;
    QString sel="select *from Laboratory where room='"+searchroom+"'";
    if(qry.exec(sel)){
        if(!qry.next()){
            QString title="warning";
            QString info="无当前实验室信息";
            QMessageBox::warning(this,title,info,QMessageBox::Ok,QMessageBox::NoButton);
        }
        else{
            model4->setQuery(sel,db);
            model4->setHeaderData(0,Qt::Horizontal,QObject::tr("教室"));
            model4->setHeaderData(1,Qt::Horizontal,QObject::tr("电脑数量"));
            model4->setHeaderData(2,Qt::Horizontal,QObject::tr("示波器数量"));
            model4->setHeaderData(3,Qt::Horizontal,QObject::tr("实验箱数量"));
            model4->setHeaderData(4,Qt::Horizontal,QObject::tr("可容纳人数"));
            ui->tableView_6->setModel(model4);
        }
    }
}

//查询双击显示详细信息
void Adrights::on_tableView_6_doubleClicked(const QModelIndex &index)
{
    QAbstractItemModel *Imodel=ui->tableView_6->model();
    QModelIndex Iindex = Imodel->index(index.row(),0);  //index.row()为算选择的行号。1为所选中行的第一列。。
    QVariant datatemp=Imodel->data(Iindex);
    QString name=Imodel->data(index).toString();        //name即为所选择行的第一列的值
    qDebug()<<name<<datatemp.toString()<<index.column();
    if(index.column()==1){
        if(name!="0"){
            QString room=datatemp.toString();
            detail_inf="select *from Computer where address='"+room+"'";
            details d;
            d.exec();
        }
    }
    else if(index.column()==2){
        if(name!="0"){
            QString room=datatemp.toString();
            detail_inf="select *from Oscilloscope where address='"+room+"'";
            details d2;
            d2.exec();
        }
    }
}
