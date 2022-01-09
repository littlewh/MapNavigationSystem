#include <QCoreApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "login.h"
#include "ui_login.h"
#include "register.h"
#include "ui_register.h"
#include "md5.h"
#include "normalmap.h"
#include "privilegemap.h"
#include "map.h"


Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
   // ui->lineEdit->setStyleSheet("QLineEdit{border:2px rgb(69,192,64);border-radius:10px;padding:2px 4px;color:rgb(211,211,211);}");//提示词背景色
   // ui->lineEdit_2->setStyleSheet("QLineEdit{border:2px rgb(69,192,64);border-radius:10px;padding:2px 4px;color:rgb(211,211,211);}");//提示词背景色
    ui->lineEdit->setStyleSheet("QLineEdit{background-color:transparent}""QLineEdit{border-width:0;border-style:outset;color:rgb(211,211,211);}");
    ui->lineEdit_2->setStyleSheet("QLineEdit{background-color:transparent}""QLineEdit{border-width:0;border-style:outset;color:rgb(211,211,211);}");

    ui->pushButton_2->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: white;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_3->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: white;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton->setStyleSheet("QPushButton{background-color:rgb(69,192,64);border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color: white;}""QPushButton:hover{background-color:rgb(69,233,64); color: white;}""QPushButton:pressed{border-style: inset; }");

    ui->label_4->setStyleSheet("QLabel {background-color:rgba(0,0,0,99);border:2px rgba(211,211,211,150);border-radius:5px;padding:2px 4px;}");
    ui->lineEdit->setFocus();
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_2_clicked()
{
    this->close();
    Widget *p = new Widget();
    p->show();

}

void Login::on_pushButton_clicked()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db.close();
        db = QSqlDatabase::addDatabase("QPSQL");
        //db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QPSQL");
    }
    //QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL"); //添加数据库驱动
    db.setHostName("127.0.0.1");                         //链接数据库
    db.setDatabaseName("postgres");                     //数据库名
    db.setUserName("postgres");                        //用户名
    db.setPassword("13245413324");                    //密码
    if(!db.open())
    {
         qDebug()<<"数据库连接失败\n";
         return;
    }
    QSqlQuery query;

    QString s1 = ui->lineEdit->text();//username
    QString s2 = ui->lineEdit_2->text();//password

    //正则表达式，由数字、26个英文字母组成
    QRegularExpression re1("^[A-Za-z0-9]+$");
    QRegularExpressionMatch match1=re1.match(s1);
    QRegularExpression re2("^[A-Za-z0-9]+$");
    QRegularExpressionMatch match2=re2.match(s2);

    if (s1.isEmpty() || s2.isEmpty())//空
    {
         QMessageBox::information(NULL, "错误", "用户名或密码不能为空");
    }
    else if(!match1.hasMatch() || !match2.hasMatch())//正则表达式
    {
        QMessageBox::information(NULL, "错误", "用户名或密码只能由数字、英文字母组成");
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
    }
    else
    {
        QString s3;
        s3 =  QString::fromStdString(MD5(s2.toStdString()).toString());//MD5加密，string与Qstring相互转换

        query.exec("select *from account");
//        qDebug()<<query.size();
//
//        int n = 0;
//        if (query.size() != -1)
//        {
//            n = query.size();
//        }

        bool flag1 = false;//用户名配对
        bool flag2 = false;//密码配对
        bool flag = false;//用户类型

        while(query.next())//遍历查询
        {
            QString name = query.value(0).toString();
            QString pass = query.value(1).toString();

            if (name == s1)
            {
                flag1 = true;
            }
            if (pass == s3)
            {
                flag2 = true;
            }
            if (flag1 && flag2)
            {
                flag = query.value(2).toBool();
                break;
            }
        }

        if (flag1 == false)
        {
          QMessageBox::information(NULL, "错误", "用户不存在");
          ui->lineEdit->clear();
          ui->lineEdit_2->clear();
          ui->lineEdit->setFocus();
        }
        else if (flag2 == false)
        {
            QMessageBox::information(NULL, "错误", "密码错误");
            ui->lineEdit_2->clear();
            ui->lineEdit_2->setFocus();
        }
        else
        {
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            if (flag == true)
            {
                QMessageBox::information(NULL, "登陆成功", "管理员 "+s1+" 欢迎登录");
                this->close();
                PrivilegeMap *p  = new PrivilegeMap();
                p->showMaximized();
            }
            else
            {
                QMessageBox::information(NULL, "登陆成功", "用户 "+s1+" 欢迎使用");
                this->close();
                NormalMap *p  = new NormalMap();
                p->showMaximized();
            }

        }

    }
    db.close();


}

void Login::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{

}

void Login::on_lineEdit_2_cursorPositionChanged(int arg1, int arg2)
{

}

void Login::on_lineEdit_textEdited(const QString &arg1)
{
    ui->lineEdit_2->setStyleSheet("QLineEdit{background-color:transparent}""QLineEdit{border-width:0;border-style:outset;color:rgb(211,211,211);}");
    ui->lineEdit->setStyleSheet("QLineEdit{background-color:transparent}""QLineEdit{border-width:0;border-style:outset;color:rgb(255,255,255);}");

}

void Login::on_lineEdit_2_textEdited(const QString &arg1)
{
    ui->lineEdit->setStyleSheet("QLineEdit{background-color:transparent}""QLineEdit{border-width:0;border-style:outset;color:rgb(211,211,211);}");
    ui->lineEdit_2->setStyleSheet("QLineEdit{background-color:transparent}""QLineEdit{border-width:0;border-style:outset;color:rgb(255,255,255);}");

}

void Login::on_pushButton_3_clicked()
{
    exit(0);
}
