#ifndef ASK_H
#define ASK_H

#include <QWidget>
# include <iostream>
# include <vector>
# include <map>
# include <queue>
# include <stack>
# include <QSqlDatabase>
# include <QSqlQuery>
# include <QSqlError>
# include <QDebug>
# include <QString>
//# include "mysql.h"
using namespace std;

namespace Ui {
class Ask;
}



/*
const int MAX_NODE = 105;
const int INF = 0x7fffffff;
*/



class CNode{
public:
    CNode(){};
    CNode(int ID , QString Name , int RecommendValue , QString Introduction);
    int GetRecommendValue();
    int GetID();
    QString getIntro();
    QString GetName();
private:
    int RecommendValue;
    QString Name;
    int ID;
    QString Introduction;
    const static int MAX_NODE = 105;
};


class CEdge{
public:
    CEdge(){};
    CEdge(int id ,QString Name , int from , int to , int Distance , int Traffic, int roadStatus);
    CEdge(int id, QString Name, int from, int to, int Distance, int Traffic);
    QString getName();
    int getTo();
    int getDis();
    int getTra();
private:
    int id;
    QString Name;
    int from;
    int to;
    int Distance;
    int Traffic;
    int roadStatus;
};

class CMap{
public:
    CMap(QString kind);
    void addNode(int id, int val, QString name, QString intro);
    void addEdge(int id, int u , int v , int w , QString name , int Traffic);
    QString NearBy(int u);
    int distanceFirst(const int &u, const int &v);//如果返回值为ox7fffffff那么为无法到达 需要告知用户: 该地尚未有公共交通 建议打车前往
    int trafficFirst(const int &u, const int &v);// 同上
    void assess(int x);// 必须在使用完上两个函数之后使用 用于评价和影响traffic数值
    QString printroad();//用于输出路线 必须在完成上一个操作之后使用
    int mpp(QString s1)
    {
        return mmp[s1];
    }
    QString kind;
private:
    vector<CNode> mpNode;
    vector<CEdge> mp[105];
    vector<int> lastRoad;
    map<QString,int> mmp;
};

class PublicTrafficMap: public CMap{
public:
    PublicTrafficMap();
private:

};

class  DriveCarmap: public CMap{
public:
    DriveCarmap();
private:

};

class ks
{

public:
    ks();
    void test();
    bool query(QString Table);
    bool query(QString table, QString where, QString value);
    bool query(QString table, QString where1, QString where2, QString value1, QString value2);
    void update(QString table, QString where1, QString set, QString gvalue, QString value);
    void initNode(std::vector<CNode> a);
    void initEdge(std::vector<CEdge> a[]);
    QSqlQuery getQuery();
    ~ks();
private:
    QSqlQuery check;
    QSqlDatabase database;
    QSqlQuery Query;
};
class Ask : public QWidget
{
    Q_OBJECT

public:
    explicit Ask(QWidget *parent = nullptr);
    ~Ask();

private slots:
    void on_backButton_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

private:
    Ui::Ask *ui;
    DriveCarmap *dmap;
    PublicTrafficMap *tmap;
    bool flag1 = false;
    bool flag2 = false;
};

#endif // ASK_H
