/*

题目：
    在10*10的屋子中有n*3个障碍物，现给出这n*3个障碍物的坐标，问如何从(0,5)绕过
    障碍物到达(10,5)。

分析：
    最短路加枚举判断线段是否相交。

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int X = 1005;
#define INF 1.0e10
#define esp 0.00000001

int n,m;
bool use[X];
double dis[X],map[X][X];

struct node
{
    double x,y;
    friend bool operator < (node a,node b)
    {
        return (a.x<b.x||(a.x==b.x&&a.y<b.y));
    }
}p[X];

void dijkstra() //最短路
{
    memset(use,false,sizeof(use));
    for(int i=0;i<=n;i++)
        dis[i] = INF;
    dis[0] = 0;
    double MIN;
    int k;
    for(int i=0;i<=n;i++)
    {
        MIN = INF;
        for(int j=0;j<=n;j++)
            if(!use[j]&&dis[j]<MIN)
                MIN = dis[k = j];
        use[k] = true;
        for(int j=1;j<=n;j++)
            if(!use[j])
                dis[j] = min(dis[j],dis[k]+map[k][j]);
    }
    printf("%.2lf\n",dis[n]);
}

int dcmp(double x)  //精度0
{
    if(abs(x)<esp)
        return 0;
    return x>0?1:-1;
}

bool between(node a,node b,node o)  //判断点是否在线段上
{
    if(o.x>=min(a.x,b.x)&&o.x<=max(a.x,b.x))
        return true;
    return false;
}

int det(node a,node b,node o)   //叉积
{
    return dcmp((a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y));
}

bool segment(node a,node b,node c,node d)   //判断线段是否相交
{
    int d1 = det(a,b,c);
    int d2 = det(a,b,d);
    int d3 = det(c,d,a);
    int d4 = det(c,d,b);
    if((d1^d2)==-2&&(d3^d4)==-2)
        return true;
    else if(d1==0&&between(a,b,c))
        return true;
    else if(d2==0&&between(a,b,d))
        return true;
    else if(d3==0&&between(c,d,a))
        return true;
    else if(d4==0&&between(c,d,b))
        return true;
    else
        return false;
}

double dist(int i,int j)
{
    double x = p[i].x-p[j].x;
    double y = p[i].y-p[j].y;
    return sqrt(x*x+y*y);
}

double make_map()
{
    bool ok = true;
    node temp;
    for(int i=1;i<n;i+=4)   //判断能否障碍物没有阻碍起点到终点的
    {
        temp.x = p[i].x;
        temp.y = 0;
        if(segment(temp,p[i],p[0],p[n]))
        {
            ok = false;
            break;
        }
        if(segment(p[i+1],p[i+2],p[0],p[n]))
        {
            ok = false;
            break;
        }
        temp.x = p[i].x;
        temp.y = 10.0;
        if(segment(temp,p[i+3],p[0],p[n]))
        {
            ok = false;
            break;
        }
    }
    if(ok)
        return dist(0,n);
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
            map[i][j] = INF;
        map[i][i] = 0;
    }
    int a,b,c,d;

    for(int i=5;i<n;i++)    //相邻的总可以直接到达
        for(int j=i-4;j<i;j++)
            map[i][j] = map[j][i] = dist(i,j);

    for(int i=1;i<n;i++) //枚举任意两点障碍物的顶点坐标，枚举他们中间的障碍物是否阻碍他们
    {
        a = (i-1)>>2;
        for(int j=i+1;j<n;j++)
        {
            b = (j-1)>>2;
            if(a==b)
                continue;
            ok = true;
            c = min(a,b);
            c <<= 2;
            d = max(a,b);
            d <<= 2;
            for(int k=c+5;k<=d;k+=4)
            {
                temp.x = p[k].x;
                temp.y = 0;
                if(segment(temp,p[k],p[i],p[j]))
                {
                    ok = false;
                    break;
                }

                if(segment(p[k+1],p[k+2],p[i],p[j]))
                {
                    ok = false;
                    break;
                }

                temp.x = p[k].x;
                temp.y = 10.0;
                if(segment(temp,p[k+3],p[i],p[j]))
                {
                    ok = false;
                    break;
                }
            }
            if(ok)
                map[i][j] = map[j][i] = dist(i,j);
        }
    }

    for(int i=1;i<=4;i++)   //预处理终点最近的3个障碍物以及起点最近的3个障碍物的距离
        map[0][i] = map[i][0] = dist(0,i);
    for(int i=n-4;i<n;i++)
        map[n][i] = map[i][n] = dist(n,i);

    for(int i=1;i<n;i++)    //起点与各点是否可以直接到达
    {
        a = i>>2;
        a <<= 2;
        ok = true;
        for(int j=1;j<=a;j+=4)  //每次枚举中间的障碍物
        {
            temp.x = p[j].x;
            temp.y = 0.0;
            if(segment(temp,p[j],p[0],p[i]))
            {
                ok = false;
                break;
            }
            if(segment(p[j+1],p[j+2],p[0],p[i]))
            {
                ok = false;
                break;
            }
            temp.x = p[j].x;
            temp.y = 10.0;
            if(segment(temp,p[j+3],p[0],p[i]))
            {
                ok = false;
                break;
            }
        }
        if(ok)
            map[0][i] = map[i][0] = dist(0,i);
    }

    for(int i=1;i<n;i++)    //终点与各点是否可以直接到达
    {
        a = (i-1)>>2;
        a++;
        a <<= 2;
        ok = true;
        for(int j=a+1;j<n;j+=4)
        {
            temp.x = p[j].x;
            temp.y = 0.0;
            if(segment(temp,p[j],p[n],p[i]))
            {
                ok = false;
                break;
            }
            if(segment(p[j+1],p[j+2],p[n],p[i]))
            {
                ok = false;
                break;
            }
            temp.x = p[j].x;
            temp.y = 10.0;
            if(segment(temp,p[j+3],p[n],p[i]))
            {
                ok = false;
                break;
            }
        }
        if(ok)
            map[n][i] = map[i][n] = dist(n,i);
    }

    return -1;
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    double x,y;
    while(scanf("%d",&m),m!=-1)
    {
        n = 0;
        p[0].x = 0;
        p[0].y = 5.0;

        for(int i=0;i<m;i++)
        {
            scanf("%lf",&x);
            for(int j=0;j<4;j++)
            {
                scanf("%lf",&y);
                p[++n].x = x;
                p[n].y = y;
            }
        }
        sort(p,p+n+1);
        p[++n].x = 10.0;
        p[n].y = 5.0;
        double temp = make_map();
        if(temp>0)  //如果能够直接从起点到终点走到并且没有障碍物阻碍
        {
            printf("%.2lf\n",temp);
            continue;
        }
        dijkstra(); //求最短路
    }
    return 0;
}
