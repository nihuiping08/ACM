/*

Ƥ�˶���
������������������㣨�������θ�㣩�ļ򵥶���Σ�Ƥ�˶���˵���������A��
�ڲ������Ŀi�����ϸ����Ŀb�Ĺ�ϵ��A = i + b/2 - 1��

����ε������ʽ��A =��(aXb)/2��a,b��ʾ����

���߶������˵�����Ϊ(x1,y1)��(x2,y2)
���ϵĵ��� = gcd(x2-x1,y2-y1)+1

*/
#include <iostream>
#include <cstdio>
using namespace std;
long long gcd(long long a,long long b)  //ŷ������㷨�������Լ��
{
    if(a==0)
        return b;
    return gcd(b%a,a);
}
long long det(long long x1,long long y1,long long x2,long long y2)//���
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
