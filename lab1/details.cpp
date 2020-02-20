#include "details.h"
#include "ui_details.h"
#include<QtSql>
#include<QMessageBox>
#include <QMessageBox>
#include <QDebug>
#include<QSqlError>
#include <QSqlTableModel>
#include <QTableView>
extern QSqlDatabase db;
#pragma execution_character_set("utf-8")



extern QString detail_inf;

details::details(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::details)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QSqlQueryModel *model=new QSqlTableModel(ui->tableView);
    model->setQuery(detail_inf,db);
    ui->tableView->setModel(model);
}

details::~details()
{
    delete ui;
}
