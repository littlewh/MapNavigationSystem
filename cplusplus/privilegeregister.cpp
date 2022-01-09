#include "privilegeregister.h"
#include "ui_privilegeregister.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "md5.h"
#include "privilegemap.h"
#include "map.h"

PrivilegeRegister::PrivilegeRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrivilegeRegister)
{
    ui->setupUi(this);
    ui->lineEdit->setStyleSheet("QLineEdit{border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color:rgb(211,211,211);}");//提示词背景色
    ui->lineEdit_2->setStyleSheet("QLineEdit{border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color:rgb(211,211,211);}");//提示词背景色
    ui->lineEdit_3->setStyleSheet("QLineEdit{border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color:rgb(211,211,211);}");//提示词背景色

    ui->pushButton_2->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: white;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_3->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: white;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton->setStyleSheet("QPushButton{background-color:rgb(69,192,64);border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color: white;}""QPushButton:hover{background-color:rgb(69,233,64); color: white;}""QPushButton:pressed{border-style: inset; }");

    ui->label_4->setStyleSheet("QLabel {background-color:rgba(0,0,0,99);border:2px rgba(211,211,211,150);border-radius:5px;padding:2px 4px;}");

    ui->label_2->setStyleSheet("QLabel{color:rgb(255,255,255);}");
    ui->label_3->setStyleSheet("QLabel{color:rgb(255,255,255);}");
    ui->label_5->setStyleSheet("QLabel{color:rgb(255,255,255);}");
    ui->lineEdit->setFocus();
}

PrivilegeRegister::~PrivilegeRegister()
{
    delete ui;
}
void PrivilegeRegister::on_pushButton_2_clicked()
{
    this->close();
    Widget *p = new Widget();
    p->show();

}

void PrivilegeRegister::on_pushButton_clicked()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL"); //添加数据库驱动
    db.setHostName("127.0.0.1");                         //链接数据库
    db.setDatabaseName("postgres");                     //数据库名
    db.setUserName("postgres");                        //用户名
    db.setPassword("13245413324");                    //密码
    if(!db.open())
    {
         qDebug()<<"数据库连接失败\n";
         return;
    }

    //建表
    QSqlQuery query;

    query.exec("create table account(username varchar primary key,password varchar,userflag bool)");

    QString s1 = ui->lineEdit->text();//username
    QString s2 = ui->lineEdit_2->text();//password
    QString s3 = ui->lineEdit_3->text();//repeatpassword

    //正则表达式，由数字、26个英文字母组成
    QRegularExpression re1("^[A-Za-z0-9]+$");
    QRegularExpressionMatch match1=re1.match(s1);
    QRegularExpression re2("^[A-Za-z0-9]+$");
    QRegularExpressionMatch match2=re2.match(s2);
    QRegularExpression re3("^[A-Za-z0-9]+$");
    QRegularExpressionMatch match3=re3.match(s3);


    if (s1.isEmpty() || s2.isEmpty() || s3.isEmpty())//空
    {
         QMessageBox::information(NULL, "错误", "用户名或密码不能为空");
    }
    else if (s2 != s3)
    {
        QMessageBox::information(NULL, "错误", "两次密码输入不一致");
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
    }
    else if(!match1.hasMatch() || !match2.hasMatch() || !match3.hasMatch())//正则表达式
    {
        QMessageBox::information(NULL, "错误", "用户名或密码只能由数字、英文字母组成");
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
    }
    else
    {
        QString s4;
        s4 =  QString::fromStdString(MD5(s2.toStdString()).toString());//MD5加密，string与Qstring相互转换

        query.exec("select *from account");
        //qDebug()<<query.size();

        int n = 0;
        if (query.size() != -1)
        {
            n = query.size();
        }

        bool flag = false;

        while(query.next())//遍历查询
        {

            QString value = query.value(0).toString();
            if (value == s1)
            {
                flag = true;
                break;
            }
        }

        if (flag == true)
        {
          QMessageBox::information(NULL, "错误", "此用户名已被占用");
          ui->lineEdit->clear();
          ui->lineEdit_2->clear();
          ui->lineEdit_3->clear();
        }
        else
        {
            n++;
            //qDebug()<<n;
            //query.exec("insert into account values('"+s1+"','"+s4+"','false')");
            query.exec("insert into account values('"+s1+"','"+s4+"','true')");

            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();

            QMessageBox::information(NULL, "注册成功", "管理员 "+s1+" 欢迎使用");
            this->close();
            PrivilegeMap *p  = new PrivilegeMap();
            p->showMaximized();


        }


    }
    db.close();

}

void PrivilegeRegister::on_lineEdit_2_textEdited(const QString &arg1)
{
    ui->lineEdit_2->setStyleSheet("QLineEdit{border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color:rgb(0,0,0);}");//提示词背景色

    ui->lineEdit->setStyleSheet("QLineEdit{border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color:rgb(211,211,211);}");//提示词背景色
    ui->lineEdit_3->setStyleSheet("QLineEdit{border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color:rgb(211,211,211);}");//提示词背景色
}

void PrivilegeRegister::on_lineEdit_textEdited(const QString &arg1)
{
    ui->lineEdit->setStyleSheet("QLineEdit{border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color:rgb(0,0,0);}");//提示词背景色

    ui->lineEdit_2->setStyleSheet("QLineEdit{border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color:rgb(211,211,211);}");//提示词背景色
    ui->lineEdit_3->setStyleSheet("QLineEdit{border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color:rgb(211,211,211);}");//提示词背景色

}

void PrivilegeRegister::on_pushButton_3_clicked()
{
    exit(0);
}

void PrivilegeRegister::on_lineEdit_3_textEdited(const QString &arg1)
{
    ui->lineEdit_3->setStyleSheet("QLineEdit{border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color:rgb(0,0,0);}");//提示词背景色

    ui->lineEdit->setStyleSheet("QLineEdit{border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color:rgb(211,211,211);}");//提示词背景色
    ui->lineEdit_2->setStyleSheet("QLineEdit{border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color:rgb(211,211,211);}");//提示词背景色

}
