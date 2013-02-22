/*

题目：
    n个人围成环，给出m个人用线连着，这种线可以是在圆内，可以是在圆外，并且
    线与线之间不能够有交叉的地方，若存在这种线的话，输出。。否则输出。。

分析：
    画个圆，然后找出不可能存在相交的两组线段，然后如果线段i,j是相交的话，则
    对[i,j+m],[i+m,j],[j,j+m],[j+m,i]连线，建好一个m*2的图，然后2-sat判断是
    否成立就行了

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 1000005;
#define debug puts("here");

int stack[X],dfn[X],low[X],father[X],top,depth,bcnt;
bool instack[X];
int head[X],a[X],b[X],qq;
int n,m;

struct node
{
    int y,next;
}p[X];

void dfs(int x)
{
    low[x] = dfn[x] = ++depth;
    instack[x] = true;
    stack[++top] = x;
    int y;
    for(int i=head[x];i!=-1;i=p[i].next)
    {
        y = p[i].y;
        if(!dfn[y])
        {
            dfs(y);
            low[x] = min(low[x],low[y]);
        }
        else if(instack[y])
            low[x] = min(low[x],dfn[y]);
    }
    if(dfn[x]==low[x])
    {
        ++bcnt;
        do
        {
            y = stack[top--];
            instack[y] = true;
            father[y] = bcnt;
        }while(x!=y);
    }
}

void tarjan()
{
    memset(dfn,0,sizeof(dfn));
    memset(instack,false,sizeof(instack));
    top = bcnt = depth = 0;
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            dfs(i);
}

bool check()
{
    for(int i=1;i<=m;i++)
        if(father[i]==father[i+m])
            return false;
    return true;
}

void add(int x,int y)
{
    p[qq].y = y;
    p[qq].next = head[x];
    head[x] = qq++;
}

bool ok(int i,int j)
{
    if(a[i]<a[j]&&b[i]>b[j])
        return false;
    if(a[i]>a[j]&&b[i]<b[j])
        return false;
    if(a[i]>b[j]||a[j]>b[i])
        return false;
    return true;

}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n>>m)
    {
        memset(head,-1,sizeof(head));
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d",&a[i],&b[i]);
            a[i]++;
            b[i]++;
            if(a[i]>b[i])
                swap(a[i],b[i]);
        }
        qq = 0;
        for(int i=1;i<=m;i++)
            for(int j=i+1;j<=m;j++)
                if(ok(i,j))
                {
                    add(i,j+m);
                    add(i+m,j);
                    add(j,i+m);
                    add(j+m,i);
                }
        n = m<<1;
        tarjan();
        if(check())
            puts("panda is telling the truth...");
        else
            puts("the evil panda is lying again");
    }
    return 0;
}
