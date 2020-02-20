#ifndef ADLOG_H
#define ADLOG_H

#include <QDialog>

namespace Ui {
class ADlog;
}

class ADlog : public QDialog
{
    Q_OBJECT

public:
    explicit ADlog(QWidget *parent = nullptr);
    ~ADlog();

private slots:
    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_3_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::ADlog *ui;
};

#endif // ADLOG_H
