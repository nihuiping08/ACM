/*

题目：
    给出n棵树的价值、坐标、以及砍了它之后能够用它作为篱笆围成的长度，现在问
    如何砍一些树并利用他们围剩下的树，使得损失的价值最少

分析：
    二进制枚举要砍的树，然后计算凸包的周长，判断是否能够围成功，若成功的话，
    更新答案

*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int X = 20;
#define esp 1e-8
const int inf = 1e9;
#define debug puts("here");

int a[X],top,ans;

struct node
{
    int x,y,value,len;
    friend bool operator < (node a,node b)
    {
        return a.y<b.y||(a.y==b.y&&a.x<b.x);
    }
}p[X],res[X],in[X];

int dcmp(double x)
{
    if(abs(x)<esp)
        return 0;
    return x<0?-1:1;
}

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

double dis(double x,double y)
{
    return sqrt(x*x+y*y);
}

double dis(node a,node b)
{
    return dis(a.x-b.x,a.y-b.y);
}

void graham(int n,double len,int value)
{
    sort(p,p+n);
    top = 1;
    res[0] = p[0];
    res[1] = p[1];
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

    double temp = 0;
    for(int i=0;i<top;i++)
        temp += dis(res[i],res[i+1]);
    if(temp<len||abs(temp-len)<esp)
        ans = min(ans,value);
}

void solve(int n)
{
    ans = inf;
    int temp,cnt = 0,sum,len;
    int m = 1<<n;
    int ret;
    for(int i=1;i<m;i++)
    {
        temp = i;
        memset(a,0,sizeof(a));
        ret = sum = cnt = len = 0;
        while(temp)
        {
            a[cnt++] = temp&1;
            temp = temp>>1;
        }
        for(int j=0;j<n;j++)
        {
            if(a[j])
                p[ret++] = in[j];
            else
            {
                sum += in[j].value;
                len += in[j].len;
            }
        }
        if(ret==1)
        {
            ans = min(ans,sum);
            continue;
        }
        else if(ret==2)
        {
            if(2*dis(p[0],p[1])<len)
                ans = min(ans,sum);
            continue;
        }
        graham(ret,len,sum);
    }
    printf("The lost value is %d.\n",ans);
}

int main()
{
    freopen("sum.in","r",stdin);
    int n;
    while(cin>>n,n)
    {
        for(int i=0;i<n;i++)
            scanf("%d%d%d%d",&in[i].x,&in[i].y,&in[i].value,&in[i].len);
        solve(n);
    }
    return 0;
}
