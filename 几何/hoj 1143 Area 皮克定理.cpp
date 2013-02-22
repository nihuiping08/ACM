/*

皮克定理：
给定顶点座标均是整点（或正方形格点）的简单多边形，皮克定理说明了其面积A和
内部格点数目i、边上格点数目b的关系：A = i + b/2 - 1。

多边形的面积公式：A =∑(aXb)/2，a,b表示向量

设线段两个端点坐标为(x1,y1)和(x2,y2)
边上的点数 = gcd(x2-x1,y2-y1)+1

*/
#include <iostream>
#include <cstdio>
using namespace std;
long long gcd(long long a,long long b)  //欧几里德算法，求最大公约数
{
    if(a==0)
        return b;
    return gcd(b%a,a);
}
long long det(long long x1,long long y1,long long x2,long long y2)//叉积
{
    return x1*y2-x2*y1;
}
void solve()
{
    long long x,y,dx,dy,px,py,area,b,I;
    px = py = area = b = I = 0;
    int n;
    cin>>n;
    for(long long i=1;i<=n;i++)
    {
        cin>>dx>>dy;
        x = px+dx;
        y = py+dy;
        if(dx<0)    dx = -dx;
        if(dy<0)    dy = -dy;
        area += det(px,py,x,y);
        b += gcd(dx,dy);
        px = x;
        py = y;
    }
    if(area<0)  area = -area;
    I = (area-b)/2+1;
    if(area%2)
        printf("%lld %lld %lld.5\n",I,b,area/2);
    else
        printf("%lld %lld %lld.0\n",I,b,area/2);
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        printf("Scenario #%d:\n",i);
        solve();
        printf("\n");
    }

    return 0;
}
