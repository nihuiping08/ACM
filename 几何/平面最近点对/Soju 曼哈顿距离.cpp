/*

题目：
    给出两个点集，然后求一个点集中到另一个点集的最小距离（曼哈顿距离）

分析：
    就是求平面最近点对问题的变形，只要使用一个标记表示在哪个集合中，在
    求曼哈顿距离的时候，若在同一集合中返回一个00，否则返回一个距离并更
    新答案

*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int X = 100005;
const int inf = 1e9;
#define debug puts("here");

int n;

struct node
{
    int x,y;
    int id;
    bool flag;
    void input(bool _flag)
    {
        flag = _flag;
        scanf("%d%d",&x,&y);
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

int dis(node a,node b)
{
    if(a.flag==b.flag)
        return inf;
    int x = a.x-b.x;
    int y = a.y-b.y;
    return max(x,-x)+max(y,-y);
}

int getmin(int l,int r,node *a)
{
    if(r-l<=2)
    {
        int ans = inf;
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
    int ans = min(getmin(l,mid,ly),getmin(mid+1,r,ry));
    int line = p[mid].x;
    k = 0;
    for(int i=0;i<=len;i++)
        if(a[i].x-line<ans)
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
    int ncase,m;
    cin>>ncase;
    while(ncase--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            p[i].input(true);
        scanf("%d",&m);
        m += n;
        for(int i=n;i<m;i++)
            p[i].input(false);
        n = m;
        sort(p,p+n,cmpx);
        for(int i=0;i<n;i++)
            p[i].id = i;
        memcpy(q,p,n*sizeof(node));
        sort(q,q+n,cmpy);
        printf("%d\n",getmin(0,n-1,q));
    }
    return 0;
}
