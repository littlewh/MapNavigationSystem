#include "ask.h"
#include "ui_ask.h"
#include <QPainter>
#include <QBitmap>
#include <QPalette>
#include <QMessageBox>
#include <QInputDialog>

Ask::Ask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ask)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    //setWindowOpacity(0.88);
    //setAttribute(Qt::WA_TranslucentBackground, true);
    //setGeometry(450,200,800,400);

    tmap = new PublicTrafficMap();
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
    ui->lineEdit_2->setStyleSheet("QLineEdit{border-radius:5px;padding:2px 4px;border-style:outset;color:rgb(211,211,211);}");

//    QIcon ico1(":/img/images/search.png");
//    ui->pushButton_3->setIcon(ico1);
    ui->lineEdit->setFocus();


}

Ask::~Ask()
{
    delete ui;
}

CNode::CNode(int ID , QString Name , int RecommendValue , QString Introduction):
    ID(ID) , Name(Name) , RecommendValue(RecommendValue) , Introduction(Introduction){
}

int CNode::GetRecommendValue(){
    return RecommendValue;
}

QString CNode::getIntro(){
    return Introduction;
}

int CNode::GetID(){
    return ID;
}

QString CNode::GetName(){
    return Name;
}

CEdge::CEdge(int id ,QString Name , int from , int to , int Distance , int Traffic, int roadStatus)
    :id(id), Name(Name), from(from), to(to), Distance(Distance), Traffic(Traffic), roadStatus(roadStatus){};

CEdge::CEdge(int id, QString Name, int from, int to, int Distance, int Traffic)
    :id(id), Name(Name), from(from), to(to), Distance(Distance), Traffic(Traffic){};

QString CEdge::getName(){
    return Name;
};

int CEdge::getTo(){
    return to;
};

int CEdge::getDis(){
    return Distance;
};

int CEdge::getTra(){
    return Traffic;
};

void CMap::addNode(int id, int val, QString name, QString intro){
    CNode temp(id , name , val , intro);

//    qDebug()<<"mmp["<<name<<"] = "<<id<<";";

//    mmp[name] = id;
    //qDebug() << temp.GetID() << ' ' << temp.GetName();
    mpNode.push_back(temp);
}

void CMap::addEdge(int id, int u , int v , int w , QString name , int Traffic){
    if(u < 1 || u > 100 || v < 1 || v > 100 || w <= 0){
        cerr << "Error" << endl;
    }
    if(u == 6 && v == 21) qDebug() << "233!!!!";
    CEdge temp(id, name , u , v , w , Traffic);
    mp[u].push_back(temp);
    CEdge temp2(id, name, v, u, w, Traffic);
    mp[v].push_back(temp2);
}

CMap::CMap(QString kind){

    mmp["艾山风景名胜区"] =  1 ;
    mmp["藏马山国际旅游度假区"] =  2 ;
    mmp["大崂樱桃谷"] =  3 ;
    mmp["方特梦幻王国"] =  4 ;
    mmp["浮山森林公园"] =  5 ;
    mmp["金沙滩"] =  6 ;
    mmp["崂山风景区"] =  7 ;
    mmp["即墨古城"] =  8 ;
    mmp["灵山"] =  9 ;
    mmp["华楼游览区"] =  10 ;
    mmp["青岛大珠山景区"] =  11 ;
    mmp["青岛羊毛沟花海湿地公园"] =  12 ;
    mmp["青岛森林野生动物世界"] =  13 ;
    mmp["青岛世博园"] =  14 ;
    mmp["青岛市毛公山风景区"] =  15 ;
    mmp["少海风景区"] =  16 ;
    mmp["石老人海水浴场"] =  17 ;
    mmp["唐岛湾海滨公园"] =  18 ;
    mmp["中山公园"] =  19 ;
    mmp["青岛西"] =  20 ;
    mmp["青岛站"] =  21 ;
    mmp["青岛北"] =  22 ;
    mmp["即墨北站"] =  23 ;
    mmp["胶州北站"] =  24 ;
    mmp["青岛胶东国际机场"] =  25 ;
    mmp["蓝村站"] =  26 ;
    mmp["青岛流亭国际机场"] =  27 ;

    qDebug() << "Map";
    ks *db = new ks();
    db->query("SELECT * FROM node;");
    QSqlQuery q = db->getQuery();
    int ji = 0;
    while(q.next()){
        //qDebug() << "233";
        CMap::addNode(q.value(0).toInt(), q.value(3).toInt(), q.value(1).toString(), q.value(2).toString());
        //qDebug()<<"mmp["<<q.value(1).toString()<<"] = "<<q.value(0).toInt()<<";";
    }
    qDebug() << "kind = "<< kind;
    db->query("edge", "iscar", kind);
    QSqlQuery Query = db->getQuery();
    ji = 0;
    while(Query.next()){
        int to = Query.value(3).toInt();
        int from = Query.value(2).toInt();
        //CEdge temp(Query.value(0).toInt(), Query.value(1).toString(), Query.value(2).toInt() , Query.value(3).toInt(), Query.value(4).toInt(), Query.value(5).toInt(), Query.value(6).toInt());
        addEdge(Query.value(0).toInt(), Query.value(2).toInt(), Query.value(3).toInt(), Query.value(4).toInt()
                , Query.value(1).toString(), Query.value(5).toInt());
    //    qDebug() << ++ji << ' ' << from << ' ' << to;
    }
    //qDebug() << mp[1][2].getTo();
    delete db;
}

QString CMap::NearBy(int u){
    QString str;
    if(mp[u].size() == 0)
    {
        str = "抱歉！ 该地区附近尚未拥有公共交通 其他景点据此地较远！";
//        qDebug() << "抱歉！ 该地区附近尚未拥有公共交通 其他景点据此地较远！";
    }
    else
    {
        for(int i = 0; i < mp[u].size(); i++)
        {
            int to = mp[u][i].getTo();
            str += mpNode[to].GetName();
            str += ":";
            str += mpNode[to].getIntro();
            str += "\n";
//            qDebug() << mpNode[to].GetName();//输出景点名字
//            qDebug() << mpNode[to].getIntro();//输出景点介绍
        }
    }
    return str;
}

int CMap::distanceFirst(const int &u, const int &v){
    lastRoad.clear();
    vector <int> vis(105);
    vector <int> dis(105 , 0x7fffffff);
    vector <int> pre(105);


    struct N{
        int dis , pos;
        N(int pos , int dis): pos(pos), dis(dis){};
        N(){}
        bool operator < (const N & a) const{
            return dis > a.dis;
        }
    };

    dis[u] = 0;
    priority_queue <N> q;
    q.push(N(u , 0));

    while(!q.empty()){
        N f = q.top();
        q.pop();
        if(vis[f.pos]){
            continue;
        }
        vis[f.pos] = 1;
        for(int i = 0; i < mp[f.pos].size(); i++){
            int to = mp[f.pos][i].getTo();
            int w = mp[f.pos][i].getDis();
            int t = mp[f.pos][i].getTra();
            if(!vis[to] && dis[to] > dis[f.pos] + w){
                dis[to] = dis[f.pos] + w;
                q.push(N(to , dis[to]));
                pre[to] = f.pos;
            }
        }
    }
    int x = v;
    int y = pre[v];
    ks *db = new ks ();
    while(x){
        qDebug()<< " x = " << x << " y = " << y;
        qDebug() << "SELECT * FROM edge WHERE iscar = "+  kind + " and enodea = " + QString::number(x) + " and enodeb = " + QString::number(y) + " or iscar = " + kind + " and enodea = "+ QString::number(y) + " and enodeb = " + QString::number(x)  + ";";
        if (db->query("SELECT * FROM edge WHERE iscar = "+  kind + " and enodea = " + QString::number(x) + " and enodeb = " + QString::number(y) + " or iscar = " + kind + " and enodea = "+ QString::number(y) + " and enodeb = " + QString::number(x)  + ";")){
            QSqlQuery q = db->getQuery();
            while(q.next()){
                lastRoad.push_back(q.value(0).toInt());
                qDebug() << "There" << q.value(0).toInt();
            }
        }
        /*
        else if(db->query("edge", "enodea", "enodeb", QString::number(y), QString::number(x))){
            QSqlQuery q = db->getQuery();
            while(q.next()){
                lastRoad.push(q.value(0).toInt());
            }
            qDebug() << q.value(0).toInt();
        }
        */
        y = pre[y];
        x = pre[x];
    }
    delete db;

    return dis[v];//这里是最后的返回距离 如果是0x7fffffff那么到达不了 输出一下客套话
}

int CMap::trafficFirst(const int &u, const int &v){
    qDebug() << "Yes";
    lastRoad.clear();
    vector <int> vis(105);
    vector <int> dis(105 , 0x7fffffff);
    vector <int> pre(105);


    struct N{
        int dis , pos;
        N(int pos , int dis): pos(pos), dis(dis){};
        N(){}
        bool operator < (const N & a) const{
            return dis > a.dis;
        }
    };

    dis[u] = 0;
    priority_queue <N> q;
    q.push(N(u , 0));

    while(!q.empty()){
        N f = q.top();
        q.pop();
        if(vis[f.pos]){
            continue;
        }
        vis[f.pos] = 1;
        for(int i = 0; i < mp[f.pos].size(); i++){
            int to = mp[f.pos][i].getTo();
            int w = mp[f.pos][i].getDis();
            int t = mp[f.pos][i].getTra();
            if(!vis[to] && dis[to] > dis[f.pos] + w * t){
                dis[to] = dis[f.pos] + w * t;
                q.push(N(to , dis[to]));
                pre[to] = f.pos;
            }
        }
    }
    int x = v;
    int y = pre[v];
    ks *db = new ks ();
    while(x){
        qDebug()<< " x = " << x << " y = " << y;
        qDebug() << "SELECT * FROM edge WHERE iscar = "+  kind + " and enodea = " + QString::number(x) + " and enodeb = " + QString::number(y) + " or iscar = " + kind + " and enodea = "+ QString::number(y) + " and enodeb = " + QString::number(x)  + ";";
        if (db->query("SELECT * FROM edge WHERE iscar = "+  kind + " and enodea = " + QString::number(x) + " and enodeb = " + QString::number(y) + " or iscar = " + kind + " and enodea = "+ QString::number(y) + " and enodeb = " + QString::number(x)  + ";")){
            QSqlQuery q = db->getQuery();
            while(q.next()){
                lastRoad.push_back(q.value(0).toInt());
                qDebug() << "There" << q.value(0).toInt();
            }
        }
        /*
        else if(db->query("edge", "enodea", "enodeb", QString::number(y), QString::number(x))){
            QSqlQuery q = db->getQuery();
            while(q.next()){
                lastRoad.push(q.value(0).toInt());
            }
            qDebug() << q.value(0).toInt();
        }
        */
        y = pre[y];
        x = pre[x];
    }
    delete db;

    return dis[v];//这里是最后的返回距离 如果是0x7fffffff那么到达不了 输出一下客套话
}

void CMap::assess(int good){//评价

    //星级 这里收集一下用户的反馈

    int f = good - 3;

    ks * bd = new ks();
    for(int i=0; i<lastRoad.size(); i++){
        int t = lastRoad[i];
        bd->query("edge", "eid", QString::number(t));
        QSqlQuery q = bd->getQuery();
        while(q.next()){
            int tra = q.value(5).toInt() + f;
            qDebug() << "tra = " << tra;
            if(tra < 5) tra = 5;// 保证traffic至少为5
            if(tra > 100) tra = 100;
            bd->update("edge", "eid", "traffic", QString::number(tra), QString::number(t));
        }
    }
}

DriveCarmap::DriveCarmap(): CMap("1"){
    kind = "1";
};

PublicTrafficMap::PublicTrafficMap(): CMap("0"){
    kind = "0";
};

ks::ks()
{
    qDebug() << "开始链接!";
//    if(QSqlDatabase::contains()){
//        qDebug() << "111!";
//        database = QSqlDatabase::database();
//    }
//    else{
        qDebug() << "222!";
        QSqlDatabase database;
        if(QSqlDatabase::contains("qt_sql_default_connection"))
        {
            database.close();
            database = QSqlDatabase::addDatabase("QMYSQL");
            //db = QSqlDatabase::database("qt_sql_default_connection");
        }
        else
        {
            database = QSqlDatabase::addDatabase("QPSQL");
        }
//        QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
        database.setHostName("127.0.0.1");
        database.setPort(3306);
        database.setDatabaseName("ks");
        database.setUserName("root");
        database.setPassword("yz010108");
        if (!database.open()) {
           qDebug("Sql connect failed.");
           qDebug() << database.lastError().text();
        } else {
            qDebug("Sql connected.");
        }
        Query = QSqlQuery(database);
    //}
   // qDebug() << "链接成功!";
}

QString CMap::printroad()
{
    qDebug()<< "size = " << lastRoad.size();
    QString str;
    for(int i=lastRoad.size() - 1; i>=0; i--)
    {
        int t = lastRoad[i];
        ks *db = new ks();
        db->query("edge", "eid", QString::number(t));
        QSqlQuery q = db->getQuery();
        while(q.next())
        {
            str += q.value(1).toString();
            qDebug() << q.value(1).toString();
            str+="->";
        }
    }
    qDebug()<<"printtest2";
    cout << endl;
    qDebug() << str;
    return str;
}

bool ks::query(QString Table){
    if(!Query.exec(Table)){// 查询table
       //  qDebug() << database.lastError().text();
         return false;
    }
    else{
//        while(Query.next()){
//            QString con = Query.value(0).toString();
//           qDebug() << con;//链接测试
//        }
        return true;
    }
}
bool ks::query(QString table, QString where, QString value){
    if(!Query.exec("SELECT * FROM " + table + " WHERE " + where + "=" + value + ";")){
        qDebug() << database.lastError().text();
        return false;
    }
    else{
        qDebug() << "SELECT * FROM " + table + " WHERE " + where + "=" + value + ";";
        return true;
    }
}

bool ks::query(QString table, QString where1, QString where2, QString value1, QString value2){
    qDebug() << "SELECT * FROM " + table + " WHERE " + where1 + " = '" + value1 + "' and " + where2 + " = '" + value2 + "';";
    if(!Query.exec("SELECT * FROM " + table + " WHERE " + where1 + " = '" + value1 + "' and " + where2 + " = '" + value2 + "';")){
     //   qDebug() << database.lastError().text();
        return false;
    }
    else{
        /*
        while(Query.next()){
           QString con = Query.value(0).toString();
           qDebug() << con;//链接测试
        }
        */
        return true;
    }
    //qDebug() << query;
    //Query.exec(query);
}

void ks::update(QString table, QString where, QString set, QString gvalue, QString value){// 更新一个位置
    Query.exec("UPDATE " + table + " SET " + set + " = " +  gvalue + " " + "WHERE " + where + " = " + value + ";");
    qDebug() << "UPDATE " + table + " SET " + set + " = " +  gvalue + " " + "WHERE " + where + " = " + value + ";";
    //qDebug() << update;
    //check.exec(update);
}

void ks::initNode(vector<CNode> a){
    while(Query.next()){
        CNode temp(Query.value(0).toInt(), Query.value(1).toString(), Query.value(3).toInt(), Query.value(2).toString());
        a.push_back(temp);
    }
}
/*
void ks::initEdge(vector<CEdge> *a){
    while(Query.next()){
        int to = Query.value(3).toInt();
        int from = Query.value(2).toInt();
        qDebug() << to << ' ' << from;
        CEdge temp(Query.value(0).toInt(), Query.value(1).toString(), Query.value(2).toInt() , Query.value(3).toInt(), Query.value(4).toInt(), Query.value(5).toInt(), Query.value(6).toInt());
        a[to].push_back(temp);
        a[from].push_back(temp);
    }
}
*/
QSqlQuery ks::getQuery(){
    return Query;
}

ks::~ks()
{

}

void Ask::on_backButton_clicked()
{
    if(this->flag1 || this->flag2)
    {
        if (this->flag1)
        {
            bool ok;
            int value = QInputDialog::getInt(this,tr("请输入您对该路线路况的评价:"),tr("请输入1到5之间的正整数"),3,1,5,1,&ok);
            if (ok)
            {
                tmap->assess(value);
            }
        }
        else
        {
            bool ok;
            int value = QInputDialog::getInt(this,tr("请输入您对该路线路况的评价:"),tr("请输入1到5之间的正整数"),3,1,5,1,&ok);
            if (ok)
            {
                dmap->assess(value);
            }
        }
    }
    this->close();
}

void Ask::on_pushButton_3_clicked()
{
    if (ui->lineEdit->text() == "" || ui->lineEdit_2->text() == "")
    {
        QMessageBox::information(NULL, "错误", "请输入起点和终点");
    }
    else if (!ui->radioButton->isChecked() && !ui->radioButton_2->isChecked())
    {
        QMessageBox::information(NULL, "错误", "请选择一种出行方式");
    }
    else if (tmap->mpp(ui->lineEdit->text()) == 0 || tmap->mpp(ui->lineEdit_2->text()) == 0)
    {
        QMessageBox::information(NULL, "错误", "地图中尚无该地点");
    }
    else
    {

        ui->textEdit->clear();
        ui->textEdit->setStyleSheet("QTextEdit{background:white}""QTextEdit{border-width:0;border-radius:2px;padding:2px 4px;}");
        QString s1,s2;
        //QString s1 = "\"";
        s1 += ui->lineEdit->text();
        //s1 += "\"";
        //QString s2 = "\"";
        s2 += ui->lineEdit_2->text();
        //s2 += "\"";
        qDebug()<<"ssnumber"<<s1<<" "<<s2;

        if (ui->radioButton->isChecked())
        {
            this->flag1 = true;
            //PublicTrafficMap *tmap = new PublicTrafficMap();
            int x;
            int f1 = tmap->mpp(s1);
            int f2 = tmap->mpp(s2);

            qDebug()<<"number"<<f1<<" "<<f2;

            x = tmap->distanceFirst(f1,f2);
            ui->textEdit->insertPlainText("距离最近:\n");
            if (x == 0x7fffffff)
            {
                ui->textEdit->insertPlainText("抱歉，这两个景点间距离过远，无法通过此方式出行。\n");
            }
            else
            {
                ui->textEdit->insertPlainText("通过此方式出行的距离为:");
                ui->textEdit->insertPlainText(QString::number(x));
                ui->textEdit->insertPlainText("\n");
                QString ss = tmap->printroad();
                ui->textEdit->insertPlainText(ss);
                ui->textEdit->insertPlainText(s2);
                //qDebug()<<x;
            }

            x = tmap->trafficFirst(f1,f2);
            ui->textEdit->insertPlainText("\n\n\n路况最好:\n");
            if (x == 0x7fffffff)
            {
                ui->textEdit->insertPlainText("抱歉，这两个景点间距离过远，无法通过此方式出行。\n");
            }
            else
            {
            //    ui->textEdit->insertPlainText("通过此方式出行的距离为:");
             //   ui->textEdit->insertPlainText(QString::number(x));
            //    ui->textEdit->insertPlainText("\n");
                QString ss = tmap->printroad();
                ui->textEdit->insertPlainText(ss);
                ui->textEdit->insertPlainText(s2);
                //qDebug()<<x;
            }

        }
        else
        {
            this->flag2 = true;
            //DriveCarmap *p = new DriveCarmap();
            int x;
            int f1 = dmap->mpp(s1);
            int f2 = dmap->mpp(s2);
            x = dmap->distanceFirst(f1,f2);

            qDebug()<<"number"<<f1<<" "<<f2;

            ui->textEdit->insertPlainText("距离最近:\n");
            if (x == 0x7fffffff)
            {
                ui->textEdit->insertPlainText("抱歉，这两个景点间距离过远，无法通过此方式出行。\n");
            }
            else
            {
                ui->textEdit->insertPlainText("通过此方式出行的距离为:");
                ui->textEdit->insertPlainText(QString::number(x));
                ui->textEdit->insertPlainText("\n");
                QString ss = dmap->printroad();
                ui->textEdit->insertPlainText(ss);
                ui->textEdit->insertPlainText(s2);
                //qDebug()<<x;
            }

            x = dmap->trafficFirst(f1,f2);
            ui->textEdit->insertPlainText("\n\n\n路况最好:\n");
            if (x == 0x7fffffff)
            {
                ui->textEdit->insertPlainText("抱歉，这两个景点间距离过远，无法通过此方式出行。\n");
            }
            else
            {
               // ui->textEdit->insertPlainText("通过此方式出行的距离为:");
                //ui->textEdit->insertPlainText(QString::number(x));
                //ui->textEdit->insertPlainText("\n");
                QString ss = dmap->printroad();
                ui->textEdit->insertPlainText(ss);
                ui->textEdit->insertPlainText(s2);
                //qDebug()<<x;
            }


        }
    }
}

void Ask::on_lineEdit_textEdited(const QString &arg1)
{
    ui->textEdit->clear();
    ui->textEdit->setStyleSheet("QTextEdit{background:transparent}""QTextEdit{border-width:0;border-radius:2px;padding:2px 4px;}");
    ui->lineEdit->setStyleSheet("QLineEdit{border-radius:5px;padding:2px 4px;border-style:outset;color:rgb(0,0,0);}");
    ui->lineEdit_2->setStyleSheet("QLineEdit{border-radius:5px;padding:2px 4px;border-style:outset;color:rgb(211,211,211);}");

}

void Ask::on_lineEdit_2_textEdited(const QString &arg1)
{
    ui->textEdit->clear();
    ui->textEdit->setStyleSheet("QTextEdit{background:transparent}""QTextEdit{border-width:0;border-radius:2px;padding:2px 4px;}");
    ui->lineEdit_2->setStyleSheet("QLineEdit{border-radius:5px;padding:2px 4px;border-style:outset;color:rgb(0,0,0);}");
    ui->lineEdit->setStyleSheet("QLineEdit{border-radius:5px;padding:2px 4px;border-style:outset;color:rgb(211,211,211);}");

}
