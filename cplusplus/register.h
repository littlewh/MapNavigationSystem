#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include "widget.h"

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots://槽声明
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_textEdited(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_lineEdit_3_textEdited(const QString &arg1);

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
