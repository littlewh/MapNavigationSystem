#include "recommendation.h"
#include "ui_recommendation.h"
#include "kmp.h"
#include <string>
#include <QFile>
#include <qmap.h>
#include <QPainter>
#include <QBitmap>
#include <QPalette>
using std::string;

QMap<int,QString> ma;
Recommendation::Recommendation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Recommendation)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);
    //setWindowOpacity(0.88);
    //setAttribute(Qt::WA_TranslucentBackground, true);
    //setGeometry(450,200,800,400);

    ui->backButton->setCursor(QCursor(Qt::PointingHandCursor));
    ui->backButton->setStyleSheet("QPushButton{background-color:transparent;border-width:0;border-radius:20px;color: black;}""QPushButton:hover{background-color:rgb(255,0,0);color:white;}");


    QBitmap bmp(this->size());//重写paintEvent,使用QPainter来绘制背景
    bmp.fill();
    QPainter qw(&bmp);
    qw.setPen(Qt::NoPen);
    qw.setBrush(Qt::black);
    qw.drawRoundedRect(bmp.rect(),20,20);//圆角
    setMask(bmp);


    ui->textEdit->setStyleSheet("QTextEdit{background:transparent}""QTextEdit{border-width:0;border-radius:2px;padding:2px 4px;}");
    ui->pushButton->setStyleSheet("QPushButton{background-color:rgb(69,192,64);border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color: white;}""QPushButton:hover{background-color:rgb(69,233,64); color: white;}""QPushButton:pressed{border-style: inset; }");
    ui->lineEdit->setStyleSheet("QLineEdit{border-radius:5px;padding:2px 4px;border-style:outset;color:rgb(211,211,211);}");
    ui->lineEdit->setFocus();
    //map映射
    ma[1] = "艾山风景名胜区";
    ma[2] = "藏马山国际旅游度假区";
    ma[3] = "大崂樱桃谷";
    ma[4] = "方特梦幻王国";
    ma[5] = "浮山森林公园";
    ma[6] = "华楼游览区";
    ma[7] = "即墨古城";
    ma[8] = "金沙滩";
    ma[9] = "崂山风景区";
    ma[10] = "灵山";
    ma[11] = "青岛大珠山景区";
    ma[12] = "青岛森林野生动物世界";
    ma[13] = "青岛世博园景区";
    ma[14] = "青岛市城阳毛公山风景区";
    ma[15] = "青岛羊毛沟花海湿地公园";
    ma[16] = "少海风景区";
    ma[17] = "石老人海水浴场";
    ma[18] = "唐岛湾滨海公园";
    ma[19] = "中山公园";
}

Recommendation::~Recommendation()
{
    delete ui;
}

void Recommendation::on_pushButton_clicked()
{
    ui->textEdit->setStyleSheet("QTextEdit{background:white}""QTextEdit{border-width:0;border-radius:2px;padding:2px 4px;}");

        QString str = ui->lineEdit->text();

        int ans[35];
        int cnt = 0;
        for (int i = 1;i <= 19;i++)
        {
            QString num = QString::number(i);
            QString str2 = ":/img/resourses/info";
            str2 += num;
            str2 += ".txt";

            QFile file(str2);
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            QString t = file.readAll();

            KMP *p = new KMP();
            if (p->kmp(t,str) == 1)
            {
                cnt++;
                ans[cnt] = i;
            }

        }

        if (cnt == 0)
        {
            ui->textEdit->clear();
            ui->textEdit->setText("很抱歉，不能根据您的关键词为您推荐景点，请尝试更换关键词重试。");
        }
        else
        {
            ui->textEdit->clear();
            ui->textEdit->insertPlainText("根据您提供的关键词，我们为您推荐以下景点:\n");
            for (int i = 1;i <= cnt;i++)
            {
                ui->textEdit->insertPlainText(ma[ans[i]]+"\n");
            }
        }

}

void Recommendation::on_lineEdit_textEdited(const QString &arg1)
{
    ui->textEdit->clear();
    ui->textEdit->setStyleSheet("QTextEdit{background:transparent}""QTextEdit{border-width:0;border-radius:2px;padding:2px 4px;}");
    ui->lineEdit->setStyleSheet("QLineEdit{border-radius:5px;padding:2px 4px;border-style:outset;color:rgb(0,0,0);}");

}

void Recommendation::on_lineEdit_textChanged(const QString &arg1)
{
    ui->textEdit->clear();
    ui->textEdit->setStyleSheet("QTextEdit{background:transparent}""QTextEdit{border-width:0;border-radius:2px;padding:2px 4px;}");
    ui->lineEdit->setStyleSheet("QLineEdit{border-radius:5px;padding:2px 4px;border-style:outset;color:rgb(0,0,0);}");
}

void Recommendation::on_backButton_clicked()
{
    this->close();
}
