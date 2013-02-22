/*

题目：
    给出n个矩形的左下右上坐标，求这些矩形的面积之和

分析：
    先把所有的x、y坐标用数组记录，然后对他进行排序，然后离散化成一个一个小的矩形，分别求
    所有的小矩形面积之和即可，具体看matrix67的论文

*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int X = 205;
#define inf 1e8

int lx[X],rx[X],ly[X],ry[X];
bool map[X][X];
int x[X],y[X],topx,topy;
int n;

int posx(int a)
{
    for(int i=0;i<topx;i++)
        if(x[i]==a)
            return i;
    return topx;
}

int posy(int a)
{
    for(int i=0;i<topy;i++)
        if(a==y[i])
            return i;
    return topy;
}

void addx(int a)
{
    int temp = posx(a);
    if(temp==topx)
        x[topx++] = a;
}

void addy(int a)
{
    int temp = posy(a);
    if(temp==topy)
        y[topy++] = a;
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);

    cin>>n;
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
    long long ans = 0;
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
                ans += (long long)(x[i]-x[i-1])*(y[j]-y[j-1]);
    cout<<ans<<endl;
    return 0;
}
