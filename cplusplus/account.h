#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QWidget>

namespace Ui {
class Account;
}

class Account : public QWidget
{
    Q_OBJECT

public:
    explicit Account(QWidget *parent = nullptr);
    ~Account();

private:
    QString Username;//用户名
    QString Password;//密码明文
    QString MD5_password;//密码密文
    Ui::Account *ui;
};


class Normal_account:public Account
{

    private:
        const bool Userflag = false;
};
class Privilege_account:public Account
{
    private:
        const bool Userflag = true;
};

#endif // ACCOUNT_H
