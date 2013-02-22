/*

题目：
    删除一个点后，求最大的不连通块

分析：
    对所有的割点求得删除它们之后所得的最大不连通块（在之前他们的连通块中），
    统计原图中共有的不连通块的数目，即是删除某点之后的最大不连通块的数目

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 10005;

int s[X],n,m;
int dfn[X],low[X],depth;
int head[X];

struct node
{
    int y,next;
}p[X*100];

void dfs(int x)
{
    dfn[x] = low[x] = ++depth;
    int y;
    for(int i=head[x];i!=-1;i=p[i].next)
    {
        y = p[i].y;
        if(!dfn[y])
        {
            dfs(y);
            low[x] = min(low[x],low[y]);
            if(low[y]>=dfn[x])
                s[x]++;
        }
        else
            low[x] = min(low[x],dfn[y]);
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    int x,y;
    while(cin>>n>>m,n||m)
    {
        if(!m)
        {
            printf("%d\n",n-1);
            continue;
        }
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(s,0,sizeof(s));
        depth = 0;
        int top = 0;
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&x,&y);
            p[top].y = y;
            p[top].next = head[x];
            head[x] = top++;
            p[top].y = x;
            p[top].next = head[y];
            head[y] = top++;
        }
        int scc = 0;
        int ans = 0;
        for(int i=0;i<n;i++)
            if(!dfn[i])
            {
                scc++;
                dfs(i);
                s[i]--;
            }
        for(int i=0;i<n;i++)
            ans = max(ans,s[i]);
        cout<<ans+scc<<endl;
    }
    return 0;
}
