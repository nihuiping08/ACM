/*

题目：
    给出两个点集，然后问你两个点集中的最小距离

分析：
    在求平面的最短距离的情况下，增加一个标记，若标记相同的话，就不鸟他，
    否则更新答案

*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int X = 100005;
const double inf = 1e50;
#define debug puts("here");

int n;

struct node
{
    double x,y;
    int id;
    bool flag;
    void input(bool _flag)
    {
        flag = _flag;
        scanf("%lf%lf",&x,&y);
    }
}p[X*2],q[X*2];

inline bool cmpx(const node &a,const node &b)
{
    return a.x<b.x;
}

inline bool cmpy(const node &a,const node &b)
{
    return a.y<b.y;
}

double dis(node a,node b)
{
    if(a.flag==b.flag)
        return inf;
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

double getmin(int l,int r,node *a)
{
    if(r-l<=2)
    {
        double ans = inf;
        for(int i=l;i<r;i++)
            for(int j=i+1;j<=r;j++)
                ans = min(ans,dis(p[i],p[j]));
        return ans;
    }

    int mid = (r+l)>>1;
    node *ly = new node[mid+1-l];
    node *ry = new node[r-mid+1];

    int j = 0,k = 0;
    int len = r-l;
    for(int i=0;i<=len;i++)
        if(a[i].id<=mid)
            ly[j++] = a[i];
        else
            ry[k++] = a[i];
    double ans = min(getmin(l,mid,ly),getmin(mid+1,r,ry));
    double line = p[mid].x;
    k = 0;
    for(int i=0;i<=len;i++)
        if(fabs(a[i].x-line)<ans)
            a[k++] = a[i];
    for(int i=0;i<k-1;i++)
        for(int j=i+1;j<=i+7&&j<k;j++)
            ans = min(ans,dis(a[i],a[j]));
    delete [] ly;
    delete [] ry;
    return ans;
}

int main()
{
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    while(ncase--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            p[i].input(true);
        int m = n*2;
        for(int i=n;i<m;i++)
            p[i].input(false);
        n = m;
        sort(p,p+n,cmpx);
        for(int i=0;i<n;i++)
            p[i].id = i;
        memcpy(q,p,n*sizeof(node));
        sort(q,q+n,cmpy);
        printf("%.3lf\n",sqrt(getmin(0,n-1,q)));
    }
    return 0;
}
