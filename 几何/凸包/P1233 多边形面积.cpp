/*

题目：
    多边形的面积以及周长的计算

分析：
    先求凸包，然后在判断是否在凸包中的点小于3个，小于三个即为共线，然后再用叉积求面积

*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int X = 20;

int n;

struct node
{
    int x,y;
    friend bool operator < (node a,node b)
    {
        return a.y<b.y||(a.y==b.y&&a.x<b.x);
    }
}p[X],res[X];

int det(int x1,int y1,int x2,int y2)
{
    return x1*y2-x2*y1;
}

bool del(int top,int i)
{
    if(det(res[top].x-res[top-1].x,res[top].y-res[top-1].y,p[i].x-res[top].x,p[i].y-res[top].y)<=0)
        return true;
    return false;
}

int graham()
{
    sort(p,p+n);
    res[0] = p[0];
    res[1] = p[1];
    int top = 1;
    for(int i=2;i<n;i++)
    {
        while(top&&del(top,i))
            --top;
        res[++top] = p[i];
    }
    int ntop = top;
    res[++top] = p[n-2];
    for(int i=n-3;i>=0;i--)
    {
        while(top>ntop&&del(top,i))
            --top;
        res[++top] = p[i];
    }
    return top;
}

double dist(int x,int y)
{
    return sqrt(x*x+y*y*1.0);
}

void solve()
{
    int top = graham();
    if(top<3)
    {
        printf("%.2lf\n",dist(res[top-1].x-res[0].x,res[top-1].y-res[0].y));
        printf("0.00\n");
        return;
    }
    double c = 0,area = 0;
    for(int i=1;i<=top;i++)
    {
        c += dist(res[i].x-res[i-1].x,res[i].y-res[i-1].y);
        if(i!=1&&i!=top)
            area += det(res[i].x-res[0].x,res[i].y-res[0].y,res[i-1].x-res[0].x,res[i-1].y-res[0].y);
    }
    area /= 2;
    area = max(area,-area);
    printf("%.2lf\n",c);
    printf("%.2lf\n",area);
}

int main()
{
    freopen("sum.in","r",stdin);

    cin>>n;
    for(int i=0;i<n;i++)
        cin>>p[i].x>>p[i].y;
    solve();

    return 0;
}
