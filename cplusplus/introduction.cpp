#include "introduction.h"
#include "ui_introduction.h"
#include <QFile>
#include <QPainter>
#include <QBitmap>
#include <QPalette>


Introduction::Introduction(QString num,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Introduction)
{

    setWindowFlag(Qt::FramelessWindowHint);

//        ui->backButton->setCursor(QCursor(Qt::PointingHandCursor));
//        ui->backButton->setStyleSheet("QPushButton{background-color:transparent;border-width:0;border-radius:20px;color: black;}""QPushButton:hover{background-color:rgb(255,0,0);color:white;}");



    QString str = ":/img/images/img";
    str += num;
    str += ".jpg";//确定图片路径

//    ui->label->setPixmap(QPixmap(":/img/images/img1 (1).jpg"));
    //ui->label->setStyleSheet("background-image:url(:/img/images/img1 (1).jpg)");

    QString str2 = ":/img/resourses/info";
    str2 += num;
    str2 += ".txt";//确定文件路径

    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(str));
    ui->label->setScaledContents(true);

    QFile file(str2);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QByteArray t = file.readAll();
//    QByteArray t ;
//    while(!file.atEnd())
//    {
//        t += file.readLine();
//    }
    ui->textEdit->setText(QString(t));
    file.close();
}


Introduction::~Introduction()
{
    delete ui;
}

void Introduction::on_backButton_clicked()
{
    this->close();
}
