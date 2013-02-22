/*

题目：
    输出平面最近点对的距离的一半

分析：
    利用分治法求，先对x排序，然后再对y排序并记录在另一个数组中，


*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int X = 100005;

int n;

struct node
{
    double x,y;
    int id;
    void input()
    {
        scanf("%lf%lf",&x,&y);
    }
}p[X],q[X];

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
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

double getmin(int l,int r,node *a)
{
    if(r-l<=2)
    {
        double ans = 1e50;
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
    while(scanf("%d",&n),n)
    {
        for(int i=0;i<n;i++)
            p[i].input();
        sort(p,p+n,cmpx);
        for(int i=0;i<n;i++)
            p[i].id = i;
        memcpy(q,p,n*sizeof(node));
        sort(q,q+n,cmpy);
        printf("%.2lf\n",getmin(0,n-1,q)/2);
    }
    return 0;
}
