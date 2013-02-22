/*

题目：
    寻找点集中的两个点，使得距离最远

分析：
    虽然可用枚举水过，这里用了旋转卡壳算法来做

*/
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int X = 6005;
#define esp 1e-8

int n,top;

struct node
{
    double x,y;
    friend bool operator < (node a,node b)
    {
        return a.y<b.y||(abs(a.y==b.y&&a.x<b.x));
    }
}p[X],res[X];

int dcmp(double x)
{
    if(abs(x)<esp)
        return 0;
    return x>0?1:-1;
}

int det(double x1,double y1,double x2,double y2)
{
    return dcmp(x1*y2-x2*y1);
}

bool del(int top,int i)
{
    if(det(res[top].x-res[top-1].x,res[top].y-res[top-1].y,p[i].x-res[top].x,p[i].y-res[top].y)<=0)
        return true;
    return false;
}

void graham()
{
    sort(p,p+n);
    res[0] = p[0];
    res[1] = p[1];
    top = 1;
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
}

double dis(double x,double y)
{
    return sqrt(x*x+y*y);
}

double dis(node a,node b)
{
    return dis(a.x-b.x,a.y-b.y);
}

double cross(node a,node b,node o)
{
    return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}

void solve()
{
    if(top<3)
    {
        printf("%.2lf\n",dis(res[0].x-res[1].x,res[0].y-res[1].y));
        return;
    }
    int j = 1;
    double ans = 0;
    for(int i=0;i<top;i++)
    {
        while(cross(res[i+1],res[j+1],res[i])>cross(res[i+1],res[j],res[i]))
            j = (j+1)%top;
        ans = max(ans,max(dis(res[i],res[j]),dis(res[i+1],res[j+1])));
    }
    printf("%.2lf\n",ans);
}

int main()
{
    freopen("sum.in","r",stdin);
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0;i<n;i++)
            scanf("%lf%lf",&p[i].x,&p[i].y);
        if(n==1)
        {
            puts("0");
            continue;
        }
        else if(n==2)
        {
            printf("%.2lf\n",dis(p[0].x-p[1].x,p[0].y-p[1].y));
            continue;
        }
        graham();
        solve();
    }
    return 0;
}
