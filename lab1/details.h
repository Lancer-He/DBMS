#ifndef DETAILS_H
#define DETAILS_H

#include <QDialog>

namespace Ui {
class details;
}

class details : public QDialog
{
    Q_OBJECT

public:
    explicit details(QWidget *parent = nullptr);
    ~details();

private:
    Ui::details *ui;
};

#endif // DETAILS_H
