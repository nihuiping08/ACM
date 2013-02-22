/*

题目：
    找出一个点的坐标使得与点集中距离最小的最大值

分析：
    模拟退火，拥有一个评估函数，每次往一个方向走过去，若比当前的值更优，则更新
    该值，然后继续走，直到不能走为止。

*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

const int X = 10005;
const int toe = 10000;
const int maxn = 30;
const double inf = 1e20;
#define debug puts("here");

double sx,sy;
int n;

struct node
{
    double x,y,val;
    node(){}
    node(double _x,double _y):x(_x),y(_y){}
}p[X],may[X],s,e;

inline double dis(double x,double y)
{
    return sqrt(x*x+y*y);
}

inline double dis(node a,node b)
{
    return dis(a.x-b.x,a.y-b.y);
}

double cal(node cur)
{
    double temp = inf;
    for(int i=0;i<n;i++)
        temp = min(dis(cur,p[i]),temp);
    return temp;
}

double Rand()
{
    return (rand()%(toe+1))/1.0/toe;
}

node judge(node a,node b)
{
    node cur = node(a.x+(b.x-a.x)*Rand(),a.y+(b.y-a.y)*Rand());
    cur.val = cal(cur);
    return cur;
}

void solve(double d)
{
    node temp;
    may[0] = node(0,0);
    may[1] = node(sx,0);
    may[2] = node(0,sy);
    may[3] = node(sx,sy);
    for(int i=4;i<maxn;i++)
        may[i] = judge(s,e);
    node a,b;
    while(d>0.1)
    {
        for(int i=0;i<maxn;i++)
            for(int j=0;j<maxn;j++)
            {
                a = node(max(0.0,may[i].x-d),max(0.0,may[i].y-d));
                b = node(min(sx,may[i].x+d),min(sy,may[i].y+d));

                temp = judge(a,b);
                if(temp.val>may[i].val)
                    may[i] = temp;
            }
        d *= 0.9;
    }
    temp.val = -1;
    for(int i=0;i<maxn;i++)
        if(temp.val<may[i].val)
            temp = may[i];
    printf("The safest point is (%.1lf, %.1lf).\n",temp.x,temp.y);
}

int main()
{
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    while(ncase--)
    {
        cin>>sx>>sy>>n;
        s.y = s.x = 0;
        e.x = sx;
        e.y = sy;

        for(int i=0;i<n;i++)
            scanf("%lf%lf",&p[i].x,&p[i].y);

        solve(max(e.y,e.x));
    }
    return 0;
}
