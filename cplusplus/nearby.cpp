#include "nearby.h"
#include "ui_nearby.h"
#include <QPainter>
#include <QBitmap>
#include <QPalette>
#include <QMessageBox>
#include <QInputDialog>

NearBy::NearBy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NearBy)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);
    //setWindowOpacity(0.88);
    //setAttribute(Qt::WA_TranslucentBackground, true);
    //setGeometry(450,200,800,400);

    dmap = new DriveCarmap();
    //CMap *qw = new CMap("0");

    QBitmap bmp(this->size());//重写paintEvent,使用QPainter来绘制背景
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),20,20);//圆角
    setMask(bmp);

    ui->backButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->backButton->setStyleSheet("QPushButton{background-color:transparent;border-width:0;border-radius:20px;color: black;}""QPushButton:hover{background-color:rgb(255,0,0);color:white;}");

    ui->textEdit->setStyleSheet("QTextEdit{background:transparent}""QTextEdit{border-width:0;border-radius:2px;padding:2px 4px;}");
    //ui->pushButton_3->setStyleSheet("QPushButton{background-color:rgb(69,192,64);border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color: white;}""QPushButton:hover{background-color:rgb(69,233,64); color: white;}""QPushButton:pressed{border-style: inset; }");
    ui->lineEdit->setStyleSheet("QLineEdit{border-radius:5px;padding:2px 4px;border-style:outset;color:rgb(211,211,211);}");
    ui->lineEdit->setFocus();
}

NearBy::~NearBy()
{
    delete ui;
}

void NearBy::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->textEdit->clear();
    ui->textEdit->setStyleSheet("QTextEdit{background:transparent}""QTextEdit{border-width:0;border-radius:2px;padding:2px 4px;}");
    ui->lineEdit->setStyleSheet("QLineEdit{border-radius:5px;padding:2px 4px;border-style:outset;color:rgb(0,0,0);}");
}

void NearBy::on_pushButton_3_clicked()
{
    QString sss = ui->lineEdit->text();
    if (sss == "")
    {
        QMessageBox::information(NULL, "错误", "请输入您当前所在的位置");
        ui->lineEdit->setFocus();
    }
    else
    {
        ui->textEdit->clear();
        ui->textEdit->setStyleSheet("QTextEdit{background:white}""QTextEdit{border-width:0;border-radius:2px;padding:2px 4px;}");

        int number = dmap->mpp(sss);

        QString str = dmap->NearBy(number);
        ui->textEdit->insertPlainText(str);
    }

}

void NearBy::on_backButton_clicked()
{
    this->close();
}
