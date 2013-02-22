/*

题目：
    给出n个点的坐标，问这n个点能够组成的三角形的最大面积

分析：
    先求出凸包，然后再用旋转卡壳算法求出最大面积，这个与求凸包上的最远点距离
    思想一样。

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int X = 50005;
#define debug puts("here");
const double esp = 1e-8;

int n,top;

struct node
{
    double x,y;
    friend bool operator < (node a,node b)
    {
        return a.y<b.y||(abs(a.y-b.y)<esp&&a.x<b.x);
    }
}res[X],p[X];

int dcmp(double x)
{
    if(abs(x)<esp)
        return 0;
    return x>0?1:-1;
}

int det(double x1,double y1,double x2,double y2)
{
    return dcmp(x1*y2-x2*y1);
}

bool del(int top,int i)
{
    if(det(res[top].x-res[top-1].x,res[top].y-res[top-1].y,p[i].x-res[top].x,p[i].y-res[top].y)<=0)
        return true;
    return false;
}

void graham()
{
    sort(p,p+n);
    res[0] = p[0];
    res[1] = p[1];
    top = 1;
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
        while(ntop<top&&del(top,i))
            --top;
        res[++top] = p[i];
    }
}

double cross(node a,node b,node o)
{
    return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}

void solve()
{
    if(top<3)
    {
        puts("0.00");
        return;
    }
    double ans = 0,temp;
    int k = 0;
    for(int i=0;i<top;i++)
    {
        k = (i+1)%top;
        for(int j=i+1;j<top;j++)
        {
            while(cross(res[i],res[j],res[k+1])>(temp = cross(res[i],res[j],res[k])))
                k = (k+1)%top;
            ans = max(ans,temp);
        }
    }
    printf("%.2lf\n",ans/2);
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n,n!=-1)
    {
        for(int i=0;i<n;i++)
            scanf("%lf%lf",&p[i].x,&p[i].y);
        if(n<3)
        {
            puts("0.00");
            continue;
        }
        graham();
        solve();
    }
    return 0;
}
