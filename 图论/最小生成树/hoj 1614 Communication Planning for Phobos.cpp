/*

题目：
    给出n个球面上的纬度经度的坐标，然后求最小生成树

分析：
    只要把图建立起来了，就好做了。。。

*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 105;
const double pi = acos(-1.0);
const double R = 16.7;
const double inf = 1e50;
#define debug puts("here");

double map[X][X],dis[X];
int n;
bool use[X];

struct node
{
    double x,y;
}p[X];


//计算圆心角lat表示纬度,-90<=w<=90,lng表示经度
//返回两点所在大圆劣弧对应圆心角,0<=angle<=pi
double angle(double lng1,double lat1,double lng2,double lat2)
{
    double dlng=fabs(lng1-lng2)*pi/180;
    while (dlng>=pi+pi)
        dlng-=pi+pi;
    if (dlng>pi)
        dlng=pi+pi-dlng;
    lat1*=pi/180;
    lat2*=pi/180;
    double temp = acos(cos(lat1)*cos(lat2)*cos(dlng)+sin(lat1)*sin(lat2));
    return temp*R/2;
}

void prim()
{
    for(int i=0;i<n;i++)
        dis[i] = map[0][i];
    memset(use,false,sizeof(use));
    use[0] = true;
    double ans = 0;
    double MIN;
    int k;
    for(int i=1;i<n;i++)
    {
        MIN = inf;
        for(int j=1;j<n;j++)
            if(!use[j]&&MIN>dis[j])
                MIN = dis[k = j];
        ans += MIN;
        use[k] = true;
        for(int j=1;j<n;j++)
            if(!use[j])
                dis[j] = min(dis[j],map[k][j]);
    }
    printf("%.2lf miles\n",ans);
    //debug;
}

int main()
{
    freopen("sum.in","r",stdin);
    int ncase = 0;
    while(cin>>n,n)
    {
        for(int i=0;i<n;i++)
        {
            scanf("%lf%lf",&p[i].x,&p[i].y);
            for(int j=0;j<=i;j++)//{
                map[i][j] = map[j][i] = angle(p[i].x,p[i].y,p[j].x,p[j].y);
                //cout<<map[i][j]<<endl;}
        }
        printf("Case %d: ",++ncase);
        prim();
    }
    return 0;
}
