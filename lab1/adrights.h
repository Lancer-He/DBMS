#ifndef ADRIGHTS_H
#define ADRIGHTS_H

#include <QDialog>

namespace Ui {
class Adrights;
}

class Adrights : public QDialog
{
    Q_OBJECT

public:
    explicit Adrights(QWidget *parent = nullptr);
    ~Adrights();

private slots:
    void on_lineEdit_textEdited(const QString &arg1);

    void on_spinBox_valueChanged(const QString &arg1);

    void on_spinBox_2_valueChanged(const QString &arg1);

    void on_spinBox_4_valueChanged(const QString &arg1);

    void on_spinBox_3_valueChanged(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_3_textEdited(const QString &arg1);

    void on_lineEdit_4_textEdited(const QString &arg1);

    void on_lineEdit_5_textEdited(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_9_clicked();

    void on_tableView_6_doubleClicked(const QModelIndex &index);

private:
    Ui::Adrights *ui;
};

#endif // ADRIGHTS_H
