/*

题目：
    听说lcy帮大家预定了新马泰7日游，Wiskey真是高兴的夜不能寐啊，他想着得快点
    把这消息告诉大家，虽然他手上有所有人的联系方式，但是一个一个联系过去实在
    太耗时间和电话费了。他知道其他人也有一些别人的联系方式，这样他可以通知其
    他人，再让其他人帮忙通知一下别人。你能帮Wiskey计算出至少要通知多少人，至
    少得花多少电话费就能让所有人都被通知到吗？

分析：
    因为可以通过其他人来通知他们认识的人，所以这幅图可以用强连通分量变成一个
    缩点的图，所有相互强连通分支变成一个缩点，求的所有缩点中入度为0的缩点即为
    所求的需要通知的最小人数。然后再枚举所有人所在的缩点是否入度为0，是的话更
    新该缩点所需的最小费用即可


*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int V = 1005;
const int INF = 1e9;

vector<int> adj[V];

int cost[V],n,m;
int dfn[V],low[V],father[V],stack[V],bcnt,depth,top;
bool instack[V];
int id[V],cnt[V];

void dfs(int u) //tarjan求缩点
{
    instack[u] = true;
    low[u] = dfn[u] = ++depth;
    stack[++top] = u;
    int v;
    int len = adj[u].size();
    for(int i=0;i<len;i++)
    {
        v = adj[u][i];
        if(!low[v])
        {
            dfs(v);
            low[u] = min(low[u],low[v]);
        }
        else if(instack[v])
            low[u] = min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        ++bcnt;
        do
        {
            v = stack[top--];
            instack[v] = false;
            father[v] = bcnt;
        }while(u!=v);
    }
}

void solve()
{
    depth = top = bcnt = 0;
    memset(instack,false,sizeof(instack));
    memset(low,0,sizeof(low));
    for(int i=1;i<=n;i++)
        if(!low[i])
            dfs(i);

    memset(id,0,sizeof(id));
    int v,len;
    for(int i=1;i<=n;i++)   //统计所有缩点的入度
    {
        len = adj[i].size();
        for(int j=0;j<len;j++)
        {
            v = adj[i][j];
            if(father[i]!=father[v])
                id[father[v]]++;
        }
    }
    int ci = 0;
    int ans = 0;
    for(int i=1;i<=bcnt;i++)    //缩点的数目即为bcnt
    {
        if(id[i]==0)    //统计入度为0的数目
            ci++;
        cnt[i] = INF;
    }
    for(int i=1;i<=n;i++)
    {
        v = father[i];
        if(id[v]==0)
            cnt[v] = min(cnt[v],cost[i]);   //更新费用
    }
    for(int i=1;i<=bcnt;i++)
        if(cnt[i]!=INF)
            ans += cnt[i];
    printf("%d %d\n",ci,ans);
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int x,y;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&cost[i]);
            adj[i].clear();
        }
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d",&x,&y);
            adj[x].push_back(y);
        }
        solve();
    }
    return 0;
}
