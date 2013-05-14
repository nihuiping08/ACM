#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 100002;

int p[MAX];
struct Graph
{
    int to;
    int next;
}e[MAX*4];
int index[MAX];
int edgeNum;
int seq;

int low[MAX];       //low[u]表示在树中从u点出发，经过一条其后代组成的路径和回退边，所能到达的最小深度的顶点标号
int dfn[MAX];       //dfn[u]表示结点u在树中的编号
int bridge[MAX][2],bridge_n;
int degree[MAX];
int n,m;

int min(int x, int y)
{
    return x < y ? x : y;
}

void makeSet()
{
    for(int i = 1; i <= n; i++)
        p[i] = i;
}

int findSet(int x)
{
    if(x != p[x])
        p[x] = findSet(p[x]);
    return p[x];
}

void Union(int x, int y)
{
    x = findSet(x);
    y = findSet(y);
    if(x == y)
        return;
    p[y] = x;
}

void addEdge(int from, int to)
{
    e[edgeNum].to = to;
    e[edgeNum].next = index[from];
    index[from] = edgeNum++;
    e[edgeNum].to = from;
    e[edgeNum].next = index[to];
    index[to] = edgeNum++;
}

//边连通分量，求桥
void bridge_dfs(int u, int v)
{
    int repeat = 0;                 //有平行边
    low[u] = dfn[u] = seq++;
    for(int i = index[u]; i != -1; i = e[i].next)
    {
        int w = e[i].to;
        if(w == v)
            repeat++;
        if(dfn[w] < 0)
        {
            bridge_dfs(w,u);
            low[u] = min(low[u],low[w]);
            if(!(low[w] > dfn[u]))       //不是桥，缩点
                Union(w,u);
            else
            {
                bridge[++bridge_n][0] = u;
                bridge[bridge_n][1] = w;
            }
        }
        else if(v != w || repeat != 1)
            low[u] = min(low[u],dfn[w]);
    }
}

int solve()
{
    int i;
    int a,b;
    memset(degree,0,sizeof(degree));
    for(i = 1; i <= bridge_n; i++)
    {
        a = findSet(bridge[i][0]);
        b = findSet(bridge[i][1]);
        degree[a]++;
        degree[b]++;
    }
    __int64 count = 0;
    int use[MAX] = {0};
    for(int i=1;i<=n;i++)
        use[findSet(i)]++;
    for(int i=0;i<n;i++)
        if(use[i])
            count += use[i]*(use[i]-1)/2;

    return count;
}

int main()
{
    freopen("sum.in","r",stdin);
    while(scanf("%d %d",&n,&m)!=EOF){
        int i;
        int a,b;
        edgeNum = 0;
        seq = 0;
        bridge_n = 0;
        memset(index,-1,sizeof(index));
        memset(dfn,-1,sizeof(dfn));
        for(i = 0; i < m; i++)
        {
            scanf("%d %d",&a,&b);
            addEdge(a,b);
        }
        makeSet();
        bridge_dfs(1,-1);
        printf("%d\n",solve());
    }
    return 0;
}
