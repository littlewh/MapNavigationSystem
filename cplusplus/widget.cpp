#include "widget.h"
#include "ui_widget.h"
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

//    QImage Image;
//    Image.load("D:/Documents/first/images/back2.jpeg");
//    QPixmap pixmap = QPixmap::fromImage(Image);
//    int with = ui->label->width();
//    int height = ui->label->height();
//    QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
//    //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
//    ui->label->setPixmap(fitpixmap);

    ui->pushButton->setStyleSheet("QPushButton{background-color:rgb(69,192,64);border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color: white;}""QPushButton:hover{background-color:rgb(69,233,64); color: white;}""QPushButton:pressed{border-style: inset; }");
    ui->pushButton_3->setStyleSheet("QPushButton{background-color:rgb(241,241,241);border:2px rgb(241,241,241);border-radius:5px;padding:2px 4px;color: black;}""QPushButton:hover{background-color:rgb(211,211,211); color: black;}""QPushButton:pressed{border-style: inset; }");
    ui->pushButton_2->setStyleSheet("QPushButton{background-color:rgb(135,206,250);border:2px rgb(135,206,250);border-radius:5px;padding:2px 4px;color: white;}""QPushButton:hover{background-color:rgb(0,191,255); color: white;}""QPushButton:pressed{border-style: inset; }");

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
        QMessageBox::StandardButton rb;
        rb = QMessageBox::information(NULL, "错误", "服务器连接失败，将以离线模式启动，部分功能将不可用",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if (rb == QMessageBox::Yes)
        {
            ui->pushButton->setStyleSheet("QPushButton{background-color:rgb(211,211,211);border:2px rgb(211,211,211);border-radius:5px;padding:2px 4px;color: white;}""QPushButton:hover{background-color:rgb(211,211,211); color: white;}""QPushButton:pressed{border-style: inset; }");
            ui->pushButton_2->setStyleSheet("QPushButton{background-color:rgb(211,211,211);border:2px rgb(211,211,211);border-radius:5px;padding:2px 4px;color: white;}""QPushButton:hover{background-color:rgb(211,211,211); color: white;}""QPushButton:pressed{border-style: inset; }");
            ui->pushButton->setEnabled(false);
            ui->pushButton_2->setEnabled(false);

         }

        else
        {
            exit(0);
        }

    }
    QSqlQuery query;
    query.exec("create table account(username varchar primary key,password varchar,userflag bool)");
    db.close();

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    this->close();
    Login *p = new Login();
    p->show();
}

void Widget::on_pushButton_2_clicked()
{
    this->close();
    Register *p = new Register();
    p->show();
}

void Widget::on_pushButton_3_clicked()
{
    this->close();
    Map *p = new Map();
    p->showMaximized();
    //    p->showFullScreen();
}
