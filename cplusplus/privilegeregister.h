#ifndef PRIVILEGEREGISTER_H
#define PRIVILEGEREGISTER_H

#include <QWidget>
#include "widget.h"

namespace Ui {
class PrivilegeRegister;
}

class PrivilegeRegister : public QWidget
{
    Q_OBJECT

public:
    explicit PrivilegeRegister(QWidget *parent = nullptr);
    ~PrivilegeRegister();

private slots://槽声明
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_textEdited(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_lineEdit_3_textEdited(const QString &arg1);


private:
    Ui::PrivilegeRegister *ui;
};

#endif // PRIVILEGEREGISTER_H
