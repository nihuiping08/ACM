/*

题目：
    给出n个矩形的坐标，求所有的矩形的覆盖面积

分析：
    离散化,具体请看Matrix67  http://www.matrix67.com/blog/archives/108

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int X = 205;

double x[X],y[X];
int topx,topy;
int n;
double lx[X],rx[X],ly[X],ry[X];
bool map[X][X];

int posx(double a)
{
    for(int i=0;i<topx;i++)
        if(x[i]==a)
            return i;
    return topx;
}

int posy(double a)
{
    for(int i=0;i<topy;i++)
        if(y[i]==a)
            return i;
    return topy;
}

void addx(double a)
{
    int temp = posx(a);
    if(temp==topx)
        x[topx++] = a;
}

void addy(double a)
{
    int temp = posy(a);
    if(temp==topy)
        y[topy++] = a;
}

int main()
{
    freopen("sum.in","r",stdin);
    int cnt = 0;
    while(cin>>n,n)
    {
        topx = topy = 0;
        for(int i=0;i<n;i++)
        {
            cin>>lx[i]>>ly[i]>>rx[i]>>ry[i];
            addx(lx[i]);
            addx(rx[i]);
            addy(ly[i]);
            addy(ry[i]);
        }
        sort(x,x+topx);
        sort(y,y+topy);
        double ans = 0;
        memset(map,false,sizeof(map));
        int x1,x2,y1,y2;
        for(int i=0;i<n;i++)
        {
            x1 = posx(lx[i]);
            x2 = posx(rx[i]);
            y1 = posy(ly[i]);
            y2 = posy(ry[i]);
            for(int j=x1+1;j<=x2;j++)
                for(int k=y1+1;k<=y2;k++)
                    map[j][k] = true;
        }
        for(int i=0;i<topx;i++)
            for(int j=0;j<topy;j++)
                if(map[i][j])
                    ans += (x[i]-x[i-1])*(y[j]-y[j-1]);
        printf("Test case #%d\n",++cnt);
        printf("Total explored area: %.2lf\n\n",ans);
    }
    return 0;
}
