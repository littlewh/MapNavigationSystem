#include "account.h"
#include "ui_account.h"

Account::Account(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Account)
{
    ui->setupUi(this);
}

Account::~Account()
{
    delete ui;
}
