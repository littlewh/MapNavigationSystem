#ifndef KMP_H
#define KMP_H

#include <QWidget>

class KMP
{
public:
    KMP();
    int getfail(QString &p, int plen);
    int kmp(QString &s, QString &p);
private:
    int Next[10005];
};

#endif // KMP_H
