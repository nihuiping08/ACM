/*

��Ŀ��
    ����n��͹��������Ҫ��ը��ը�ٹ̶������꣬���������������ڵ�͹���ᱻ����
    �������㱻�����͹�������

������
    ��͹��+���������

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int X = 105;
#define debug puts("here");

int top,n,a[X];
bool use[X];

struct node
{
    int x,y;
    friend bool operator < (node a,node b)
    {
        return a.y<b.y||(a.y==b.y&&a.x<b.x);
    }
}res[X],p[X],in[25][X];

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
    sort(p,p+n);
    top = 1;
    res[0] = p[0];
    res[1] = p[1];
    for(int i=2;i<n;i++)
    {
        while(top&&del(top,i))
            top--;
        res[++top] = p[i];
    }
    int mint = top;
    res[++top] = p[n-2];
    for(int i=n-3;i>=0;i--)
    {
        while(top!=mint&&del(top,i))
            --top;
        res[++top] = p[i];
    }
}

int det(node a,node b,node o)
{
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}

bool check(node cur,int id)
{
    for(int i=0;i<a[id]-1;i++)
        if(det(in[id][i],in[id][i+1],cur)*det(in[id][i+1],in[id][i+2],cur)<0)
            return false;
    return true;
}

double dis(node a,node b)
{
    return sqrt((a.x-b.x)*1.0*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

double cal(int id)
{
    double ans = 0;
    for(int i=1;i<a[id];i++)
        ans += det(in[id][i],in[id][i+1],in[id][0]);
    ans /= 2;
    ans = max(ans,-ans);
    return ans;
}

double solve(int x,int y,int cnt)
{
    node cur;
    cur.x = x;
    cur.y = y;
    for(int i=1;i<=cnt;i++)
        if(!use[i]&&check(cur,i))
        {
            use[i] = true;
            return cal(i);
        }
    return 0;
}

int main()
{
    freopen("sum.in","r",stdin);
    memset(use,false,sizeof(use));

    int cnt = 0;
    while(cin>>n,n!=-1)
    {
        for(int i=0;i<n;i++)
            scanf("%d%d",&p[i].x,&p[i].y);
        graham();
        cnt++;
        for(int i=0;i<=top;i++)
            in[cnt][i] = res[i];
        a[cnt] = top;
    }
    int x,y;
    double ans = 0;
    while(cin>>x>>y)
        ans += solve(x,y,cnt);
    printf("%.2lf\n",ans);
    return 0;
}
