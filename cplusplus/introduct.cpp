#include "introduct.h"
#include "ui_introduct.h"
#include "introduction.h"
#include <QPainter>
#include <QBitmap>
#include <QPalette>

Introduct::Introduct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Introduct)
{
    ui->setupUi(this);


    setWindowFlag(Qt::FramelessWindowHint);
    setWindowOpacity(0.88);
    //setAttribute(Qt::WA_TranslucentBackground, true);
    //setGeometry(450,200,800,400);


    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),20,20);//圆角
    setMask(bmp);

    ui->backButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_3->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_4->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_5->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_6->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_7->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_8->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_9->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_10->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_11->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_12->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_13->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_14->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_15->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_16->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_17->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_18->setCursor(QCursor(Qt::PointingHandCursor));
    ui->pushButton_19->setCursor(QCursor(Qt::PointingHandCursor));

    ui->backButton->setStyleSheet("QPushButton{background-color:transparent;border-width:0;border-radius:20px;color: black;}""QPushButton:hover{background-color:rgb(255,0,0);color:white;}");
    ui->pushButton->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_2->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_3->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_4->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_5->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_6->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_7->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_8->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_9->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_10->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_11->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_12->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_13->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_14->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_15->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_16->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_17->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_18->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");
    ui->pushButton_19->setStyleSheet("QPushButton{background-color:transparent;border-width:0;color: black;}""QPushButton:hover{text-decoration:underline;}");

}

Introduct::~Introduct()
{
    delete ui;
}
//调用景点介绍页面，根据传参确定景点
void Introduct::on_backButton_clicked()
{
    this->close();
}

void Introduct::on_pushButton_clicked()
{
    this->close();
    Introduction *p = new Introduction("1");

    p->show();

}

void Introduct::on_pushButton_2_clicked()
{
    this->close();
    Introduction *p = new Introduction("2");
    p->show();
}

void Introduct::on_pushButton_3_clicked()
{
    this->close();
    Introduction *p = new Introduction("3");
    p->show();
}

void Introduct::on_pushButton_4_clicked()
{
    this->close();
    Introduction *p = new Introduction("4");
    p->show();
}

void Introduct::on_pushButton_5_clicked()
{
    this->close();
    Introduction *p = new Introduction("5");
    p->show();
}

void Introduct::on_pushButton_6_clicked()
{
    this->close();
    Introduction *p = new Introduction("6");
    p->show();
}

void Introduct::on_pushButton_7_clicked()
{
    this->close();
    Introduction *p = new Introduction("7");
    p->show();
}

void Introduct::on_pushButton_8_clicked()
{
    this->close();
    Introduction *p = new Introduction("8");
    p->show();
}

void Introduct::on_pushButton_9_clicked()
{
    this->close();
    Introduction *p = new Introduction("9");
    p->show();
}

void Introduct::on_pushButton_10_clicked()
{
    this->close();
    Introduction *p = new Introduction("10");
    p->show();
}

void Introduct::on_pushButton_11_clicked()
{
    this->close();
    Introduction *p = new Introduction("11");
    p->show();
}

void Introduct::on_pushButton_12_clicked()
{
    this->close();
    Introduction *p = new Introduction("12");
    p->show();
}

void Introduct::on_pushButton_13_clicked()
{
    this->close();
    Introduction *p = new Introduction("13");
    p->show();
}

void Introduct::on_pushButton_14_clicked()
{
    this->close();
    Introduction *p = new Introduction("14");
    p->show();
}

void Introduct::on_pushButton_15_clicked()
{
    this->close();
    Introduction *p = new Introduction("15");
    p->show();
}

void Introduct::on_pushButton_16_clicked()
{
    this->close();
    Introduction *p = new Introduction("16");
    p->show();
}

void Introduct::on_pushButton_17_clicked()
{
    this->close();
    Introduction *p = new Introduction("17");
    p->show();
}

void Introduct::on_pushButton_18_clicked()
{
    this->close();
    Introduction *p = new Introduction("18");
    p->show();
}

void Introduct::on_pushButton_19_clicked()
{
    this->close();
    Introduction *p = new Introduction("19");
    p->show();
}
