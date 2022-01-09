#include "privilegemap.h"

PrivilegeMap::PrivilegeMap():

    Paint(10,10,1260,710),
    ReturnButton("返回",this),
    RecommendButton("景点介绍",this),
    RecommendationButton("景点推荐",this),
    PrivilegeregisterButton("注册",this),
    TrafficButton("出行建议",this),
    NearButton("附近地点",this),

    Alloffset(0,0),
    label("100%",this)
    {
        ratio= 1.0;             //初始化图片缩放比例
        action = PrivilegeMap::None;

        RecommendButton.setGeometry(1225,110,60,25);//景点介绍
        RecommendButton.setCursor(QCursor(Qt::PointingHandCursor));
        RecommendButton.setStyleSheet("QPushButton{background-color:rgb(69,192,64);border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color: white;}""QPushButton:hover{background-color:rgb(69,233,64); color: white;}""QPushButton:pressed{border-style: inset; }");
        connect(&RecommendButton,SIGNAL(clicked()),this,SLOT(onRecommendClicked()));

        RecommendationButton.setGeometry(1225,210,60,25);//景点推荐
        RecommendationButton.setCursor(QCursor(Qt::PointingHandCursor));
        RecommendationButton.setStyleSheet("QPushButton{background-color:rgb(69,192,64);border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color: white;}""QPushButton:hover{background-color:rgb(69,233,64); color: white;}""QPushButton:pressed{border-style: inset; }");
        connect(&RecommendationButton,SIGNAL(clicked()),this,SLOT(onRecommendationClicked()));

        PrivilegeregisterButton.setGeometry(1225,310,60,25);//注册管理员账户
        PrivilegeregisterButton.setCursor(QCursor(Qt::PointingHandCursor));
        PrivilegeregisterButton.setStyleSheet("QPushButton{background-color:rgb(69,192,64);border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color: white;}""QPushButton:hover{background-color:rgb(69,233,64); color: white;}""QPushButton:pressed{border-style: inset; }");
        connect(&PrivilegeregisterButton,SIGNAL(clicked()),this,SLOT(onPrivilegeregisterClicked()));

        TrafficButton.setGeometry(1225,410,60,25);//出行推荐
        TrafficButton.setCursor(QCursor(Qt::PointingHandCursor));
        TrafficButton.setStyleSheet("QPushButton{background-color:rgb(69,192,64);border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color: white;}""QPushButton:hover{background-color:rgb(69,233,64); color: white;}""QPushButton:pressed{border-style: inset; }");
        connect(&TrafficButton,SIGNAL(clicked()),this,SLOT(onTrafficonClicked()));

        NearButton.setGeometry(1225,510,60,25);//附近地点
        NearButton.setCursor(QCursor(Qt::PointingHandCursor));
        NearButton.setStyleSheet("QPushButton{background-color:rgb(69,192,64);border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color: white;}""QPushButton:hover{background-color:rgb(69,233,64); color: white;}""QPushButton:pressed{border-style: inset; }");
        connect(&NearButton,SIGNAL(clicked()),this,SLOT(onNearClicked()));

        ReturnButton.setGeometry(1225,610,60,25);//返回
        ReturnButton.setCursor(QCursor(Qt::PointingHandCursor));
        ReturnButton.setStyleSheet("QPushButton{background-color:rgb(69,192,64);border:2px rgb(69,192,64);border-radius:5px;padding:2px 4px;color: white;}""QPushButton:hover{background-color:rgb(69,233,64); color: white;}""QPushButton:pressed{border-style: inset; }");
        connect(&ReturnButton,SIGNAL(clicked()),this,SLOT(onReturnClicked()));


        label.move(840,260);
        resize(2560,1600);


        this->start();
    }

void PrivilegeMap::start()
{
    QString str = ":/img/images/mapp.png";

    if(!str.isNull())
    {

       image.load(str);
       pix = pix.fromImage(image);

       crtPix = pix;
       pixW = image.width();            //图片宽
       pixH = image.height();           //图片高
       qDebug()<<str<<pixW<<pixH;
       this->setWindowTitle("地图全阅");
    }
}
bool PrivilegeMap::event(QEvent * event)
{
    static bool press=false;
    static QPoint PreDot;

    if(event->type() == QEvent::MouseButtonPress )
    {
           QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);

           //判断鼠标是否是左键按下,且鼠标位置是否在绘画区域
           if(mouse->button()==Qt::LeftButton &&Paint.contains(mouse->pos()))
           {
               press=true;
               QApplication::setOverrideCursor(Qt::OpenHandCursor); //设置鼠标样式

               PreDot = mouse->pos();
           }

    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);

        //判断鼠标是否是左键释放,且之前是在绘画区域
        if(mouse->button()==Qt::LeftButton && press )
        {
            QApplication::setOverrideCursor(Qt::ArrowCursor); //改回鼠标样式
            press=false;
        }
    }

     if(event->type() == QEvent::MouseMove)              //移动图片
     {
          if(press)
         {
            QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(event);

            offset.setX(mouse->x() - PreDot.x());
            offset.setY(mouse->y() - PreDot.y());
            PreDot = mouse->pos();
            action = PrivilegeMap::Move;

            this->update();
         }
     }
    return QWidget::event(event);
}

void PrivilegeMap::wheelEvent(QWheelEvent* event)     //鼠标滑轮事件
{

    if (event->angleDelta().y() > 0)
    {      //上滑,缩小

       action=PrivilegeMap::Shrink;
       this->update();
    }
    else
    {                    //下滑,放大
        action=PrivilegeMap::Amplification;
        this->update();
    }
    event->accept();
}



void PrivilegeMap::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform|QPainter::Antialiasing|QPainter::TextAntialiasing);
    painter.drawRect(Paint.x()-1,Paint.y()-1,Paint.width()+1,Paint.height()+1); //画框

    if(image.isNull())
    {
     return;
    }

    int NowW = ratio *pixW;
    int NowH = ratio *pixH;

    if(action==PrivilegeMap::Shrink)           //缩小
    {
          ratio-=0.05*ratio;
        if(ratio<0.018)
          ratio = 0.01;

        /*显示比例*/
        QString str;
        str.asprintf("%.0f%",ratio*100);
        label.setText(str) ;
        qDebug()<<"缩小:"<<ratio;
    }
    else  if(action==PrivilegeMap::Amplification)           //放大
    {

         ratio+=0.05*ratio;
         if(ratio>4.5)
            ratio = 5.000;

        /*显示比例*/
        QString str;
        str.asprintf("%.0f%",ratio*100);
        label.setText(str);
        qDebug()<<"放大:"<<ratio;
    }


    if(action==PrivilegeMap::Amplification || action==PrivilegeMap::Shrink || action==PrivilegeMap::Reset)      //更新图片
    {
      NowW = ratio *pixW;
      NowH = ratio *pixH;


      crtPix= pix.scaled(NowW, NowH,Qt::KeepAspectRatio,Qt::SmoothTransformation); //重新装载

      action=PrivilegeMap::None;
    }

    if(action==PrivilegeMap::Move)                    //移动
    {
        int offsetx=Alloffset.x()+offset.x();
        Alloffset.setX(offsetx);

        int offsety=Alloffset.y()+offset.y();
        Alloffset.setY(offsety);
        action=PrivilegeMap::None;
    }

    if(abs(Alloffset.x())>=(Paint.width()/2 + NowW/2 -10))    //限制X偏移值
    {
        if(Alloffset.x()>0)
            Alloffset.setX(Paint.width()/2 + NowW/2 -10);
        else
         Alloffset.setX(-Paint.width()/2 + -NowW/2 +10);

    }
    if(abs(Alloffset.y())>=(Paint.height()/2 + NowH/2 -10))    //限制Y偏移值
    {
        if(Alloffset.y()>0)
            Alloffset.setY(Paint.height()/2 + NowH/2 -10);
        else
         Alloffset.setY(-Paint.height()/2 + -NowH/2 +10);

    }

    int x = Paint.width()/2 + Alloffset.x() -NowW/2;
    if(x<0)
        x=0;

    int y = Paint.height()/2 + Alloffset.y() -NowH/2;
    if(y<0)
        y=0;

    int  sx = NowW/2 - Paint.width()/2 - Alloffset.x();
    if(sx<0)
        sx=0;

    int  sy = NowH/2 - Paint.height()/2 - Alloffset.y();
    if(sy<0)
        sy=0;

    int w =(NowW - sx)>Paint.width()? Paint.width() : (NowW - sx);
    if(w>(Paint.width()-x))
        w = Paint.width()-x;

    int h =(NowH - sy)>Paint.height()? Paint.height() : (NowH - sy);
    if(h>(Paint.height()-y))
        h = Paint.height()-y;

    painter.drawTiledPixmap(x+Paint.x(),y+Paint.y(),w,h,crtPix,sx,sy);             //绘画图形

}

void PrivilegeMap::onRecommendClicked()
{
    Introduct *p = new Introduct();
    p->show();
}

void PrivilegeMap::onReturnClicked()
{
    this->close();
    Widget *p = new Widget();
    p->show();
}

void PrivilegeMap::onRecommendationClicked()
{
    //this->close();
    Recommendation *p = new Recommendation();
    p->show();
}

void PrivilegeMap::onPrivilegeregisterClicked()
{
    this->close();
    PrivilegeRegister *p = new PrivilegeRegister();
    p->show();
}

void PrivilegeMap::onTrafficonClicked()
{
    //this->close();
    Ask *p = new Ask();
    p->show();
}

void PrivilegeMap::onNearClicked()
{
    NearBy *p = new NearBy();
    p->show();
}

