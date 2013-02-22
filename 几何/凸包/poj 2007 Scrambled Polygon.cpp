/*

题目：
    简单的输出凸包上的点

*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int X = 105;

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

void graham()
{
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
    int ok = -1;
    for(int i=0;i<top;i++)
    {
        if(res[i].x==0&&res[i].y==0)
            ok = i;
        if(ok!=-1)
            printf("(%d,%d)\n",res[i].x,res[i].y);
    }
    for(int i=0;i<ok;i++)
        printf("(%d,%d)\n",res[i].x,res[i].y);
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int x,y;
    n = 0;
    while(scanf("%d%d",&x,&y)!=EOF)
        p[n].x = x,p[n++].y = y;
    sort(p,p+n);
    graham();
    return 0;
}
