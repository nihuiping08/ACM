/*

题目：
    给出多边形的体积以及多边形的各个点的坐标，然后问你多边形的高

分析：
    求多边形面积，叉积

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int X = 10005;
#define esp 1e-8

struct node
{
    double x,y;
}p[X];

double m;
int n;


double det(node a,node b,node o)
{
    return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n,n)
    {
        for(int i=1;i<=n;i++)
            scanf("%lf%lf",&p[i].x,&p[i].y);
        cin>>m;
        p[0] = p[n];
        double ans = 0;
        for(int i=n;i;i--)
            ans += det(p[i-1],p[i],p[0]);
        ans = max(ans,-ans);
        ans /= 2;
        printf("BAR LENGTH: %.2lf\n",m/ans);
    }
    return 0;
}
