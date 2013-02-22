/*

题目：
    寻找凸包中最远的两个点的距离平方

分析：
    旋转卡壳算法实际上是通过枚举每一条边作为底，通过边旋转找到以此边为
    三角形时的面积最大时，更新最远的距离

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int X = 50005;

struct node
{
    int x,y;
    friend bool operator < (node a,node b)
    {
        return a.y<b.y||(a.y==b.y&&a.x<b.x);
    }
}p[X],res[X];

int n,top;

int dis(node a,node b)
{
    int x = a.x-b.x;
    int y = a.y-b.y;
    return x*x+y*y;
}

int cross(node a,node b,node c)
{
    return (a.x-c.x)*(b.y-c.y)-(b.x-c.x)*(a.y-c.y);
}

void graham()
{
    sort(p,p+n);
    res[0] = p[0];
    res[1] = p[1];
    top = 1;
    for(int i=2;i<n;i++)
    {
        while(top&&cross(p[i],res[top-1],res[top])<=0)
            --top;
        res[++top] = p[i];
    }
    int ntop = top;
    res[++top] = p[n-2];
    for(int i=n-3;i>=0;i--)
    {
        while(top>ntop&&cross(p[i],res[top-1],res[top])<=0)
            --top;
        res[++top] = p[i];
    }
}

void solve()
{
    int j = 1,ans = 0;
    for(int i=0;i<top;i++)
    {   ///由于是旋转产生j,所以j可以不用回退到1
        while(cross(res[i+1],res[j+1],res[i])>cross(res[i+1],res[j],res[i]))
        {   ///其实就是根据以res[i],res[i+1]为底时求三角形面积最大时j的位置
            //cout<<res[i].x<<"  "<<res[i].y<<"   "<<res[j].x<<"  "<<res[j].y<<endl;;
            j = (j+1)%top;
        }
        //cout<<"ans = "<<res[i].x<<" "<<res[i].y<<"  "<<res[j].x<<" "<<res[j].y<<endl;
        ans = max(ans,max(dis(res[i],res[j]),dis(res[i+1],res[j+1])));
    }
    cout<<ans<<endl;
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d%d",&p[i].x,&p[i].y);
    if(n==2)
    {
        cout<<dis(p[0],p[1])<<endl;
        return 0;
    }
    graham();
    solve();
    return 0;
}
