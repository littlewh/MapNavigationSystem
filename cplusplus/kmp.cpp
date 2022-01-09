#include "kmp.h"
#include <QWidget>

KMP::KMP()
{

}
int KMP:: getfail(QString &p, int plen)//预处理
{
    Next[0] = 0;
    Next[1] = 0;
    for(int i=1; i < plen; i++)
    {
        int j = Next[i];
        while(j && p[i] != p[j])
            j = Next[j];
        Next[i+1] = (p[i] == p[j]) ? j + 1 : 0;
    }
}
int KMP::kmp(QString &s, QString &p)
{// s 是文章  p 是搜索词
    int last = -1;
    int slen = s.size();
    int plen = p.size();
    getfail(p, plen);
    int j = 0;
    for(int i=0; i < slen; i++)
    {
        while(j && s[i] != p[j])
            j = Next[j];
        if(s[i] == p[j])
            j++;
        if(j == plen)
        {
            //此处配对成功
            return 1;
        }
    }
    return 0;
}
