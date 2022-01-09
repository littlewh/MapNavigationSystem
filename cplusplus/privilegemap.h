#ifndef PRIVILEGEMAP_H
#define PRIVILEGEMAP_H


#include <QWidget>
#include <QtGui>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QApplication>
#include <QFileDialog>
#include <QImage>
#include "widget.h"
#include "introduct.h"
#include "recommendation.h"
#include "privilegeregister.h"
#include "ask.h"
#include "nearby.h"

namespace Ui {
class PrivilegeMap;
}


class PrivilegeMap : public QWidget
{
    Q_OBJECT

private :

    QPixmap  pix;
    QPixmap  crtPix;
    int action;          //动作(放大,缩小,移动...)
    int pixW;            //图片宽
    int pixH;            //图片高

    QRect Paint;         //绘画区域

    QImage image;        //打开的图片


    float ratio;              //缩放比例
    QPoint offset;           //一次的图片偏移值
    QPoint Alloffset;          //总偏移
    QLabel label;

    QPushButton ReturnButton;
    QPushButton RecommendButton;
    QPushButton RecommendationButton;
    QPushButton PrivilegeregisterButton;
    QPushButton TrafficButton;
    QPushButton NearButton;

    void AddComboItem(QComboBox* cmbo);
    bool event(QEvent * event);
    void wheelEvent(QWheelEvent* e);     //鼠标滑轮事件
private slots:
    void onReturnClicked();
    void onRecommendClicked();
    void onRecommendationClicked();
    void onPrivilegeregisterClicked();
    void onTrafficonClicked();
    void onNearClicked();

    void start();

   void paintEvent(QPaintEvent *event);
public:
    explicit PrivilegeMap();

    enum  Type {
        None          = 0,
        Amplification ,
        Shrink,
        Lift,
        Right,
        Up,
        Down,
        Move,
        Reset
    };

};


#endif // PRIVILEGEMAP_H
