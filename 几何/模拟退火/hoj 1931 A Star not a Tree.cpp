#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

const int X = 1000;
const int maxn = 30;
const double inf = 1e20;
#define debug puts("here");

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
    double temp = 0;
    for(int i=0;i<n;i++)
        temp += dis(p[i],cur);
    return temp;
}

double Rand()
{
    return rand()%(X+1)/1.0/X;
}

node judge(node a,node b)
{
    node cur = node(a.x+(b.x-a.x)*Rand(),a.y+(b.y-a.y)*Rand());
    cur.val = cal(cur);
    return cur;
}

void solve(double d)
{
    double ans = inf;
    node temp;
    for(int i=0;i<maxn;i++)
        may[i] = judge(s,e);
    while(d>0.1)
    {
        for(int i=0;i<maxn;i++)
            for(int j=0;j<maxn;j++)
            {
                temp = judge(node(may[i].x-d,may[i].y-d),node(may[i].x+d,may[i].y+d));
                if(temp.val<may[i].val)
                    may[i] = temp;
            }
        d *= 0.9;
    }
    for(int i=0;i<maxn;i++)
        ans = min(ans,may[i].val);
    printf("%.0lf\n",ans);
}

int main()
{
    freopen("sum.in","r",stdin);
    while(scanf("%d",&n)!=EOF)
    {
        s.x = inf;
        s.y = inf;
        e.x = -inf;
        e.y = -inf;

        for(int i=0;i<n;i++)
        {
            scanf("%lf%lf",&p[i].x,&p[i].y);
            s.x = min(s.x,p[i].x);
            s.y = min(s.y,p[i].y);
            e.x = max(e.x,p[i].x);
            e.y = max(e.y,p[i].y);
        }
        solve(max(e.y-s.y,e.x-s.x));
    }
    return 0;
}
