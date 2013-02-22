/*

题目：
    原先所有的木桩都在一个凸包的边上，现在有一些木桩不见了，问还能不能
    靠给出的剩余的木桩确定原来的边界

分析;
    由于现在的是剩余的木桩，我们可以先求出剩余木桩组成的凸包，而不在凸包上的
    所有木桩必定在凸包的边上，并且每条边上均含有一个非凸包顶点的点才能够确定
    边界

*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int X = 1005;
#define esp 0.00000001

int n;
bool use[X];

struct node
{
    double x,y;
    int id;
    friend bool operator < (node a,node b)
    {
        return a.y<b.y||(a.y==b.y&&a.x<b.x);
    }
}p[X],res[X];

double det(double x1,double y1,double x2,double y2)
{
    return x1*y2-x2*y1;
}

bool del(int top,int i)
{
    if(det(res[top].x-res[top-1].x,res[top].y-res[top-1].y,p[i].x-res[top].x,p[i].y-res[top].y)<=0)
        return true;
    return false;
}

bool dot(double x1,double y1,double x2,double y2,double x,double y)
{
    double a = (x1-x)*(y2-y1);
    double b = (y1-y)*(x2-x1);
    if(abs(a-b)<esp)
        return false;
    return true;
}

bool graham()
{
    memset(use,false,sizeof(use));

    res[0] = p[0];
    res[1] = p[1];
    use[0] = use[1] = true;

    int top = 1;

    for(int i=2;i<n;i++)
    {
        while(top&&del(top,i))
        {
            use[res[top].id] = false;
            --top;
        }
        use[i] = true;
        res[++top] = p[i];
    }

    int ntop = top;
    res[++top] = p[n-2];
    use[n-2] = true;
    for(int i=n-3;i>=0;i--)
    {
        while(top>ntop&&del(top,i))
        {
            use[res[top].id] = false;
            --top;
        }
        use[i] = true;
        res[++top] = p[i];
    }

    bool ok;
    for(int i=1;i<=top;i++)
    {
        ok = false;
        for(int j=0;j<n;j++)
        {
            if(use[j])
                continue;
            if(!dot(res[i].x,res[i].y,res[i-1].x,res[i-1].y,p[j].x,p[j].y))
            {
                use[j] = true;
                ok = true;
            }
        }
        if(!ok)
            return false;
    }
    for(int i=0;i<n;i++)
        if(!use[i])
            return false;
    return true;
}

bool check()    //判断是否所有的点共线，不是返回false，是返回true
{
    for(int i=2;i<n;i++)
        if(dot(p[i].x,p[i].y,p[i-1].x,p[i-1].y,p[i-2].x,p[i-2].y))
            return false;
    return true;
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int t;
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=0;i<n;i++)
        {
            scanf("%lf%lf",&p[i].x,&p[i].y);
            p[i].id = i;
        }
        if(n<6)
        {
            cout<<"NO"<<endl;
            continue;
        }
        sort(p,p+n);
        if(check())
        {
            cout<<"NO"<<endl;
            continue;
        }
        for(int i=0;i<n;i++)
            p[i].id = i;
        graham()?cout<<"YES"<<endl:cout<<"NO"<<endl;
    }
    return 0;
}
