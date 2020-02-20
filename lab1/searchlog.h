#ifndef SEARCHLOG_H
#define SEARCHLOG_H

#include <QDialog>

namespace Ui {
class searchlog;
}

class searchlog : public QDialog
{
    Q_OBJECT

public:
    explicit searchlog(QWidget *parent = nullptr);
    ~searchlog();

private slots:
    void on_pushButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::searchlog *ui;
};

#endif // SEARCHLOG_H
