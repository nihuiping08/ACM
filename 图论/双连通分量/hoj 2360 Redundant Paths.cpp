#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define maxn 5005
#define maxm 10005

struct Edge
{
    int v, next;
} edge[maxm];

int n, m;
int head[maxn];
bool hash[maxn][maxn];
int ecount, tcount;
int dfn[maxn], vis[maxn], low[maxn], degree[maxn];

void addedge(int a, int b)
{
    edge[ecount].v = b;
    edge[ecount].next = head[a];
    head[a] = ecount;
    hash[a][b] = hash[b][a] = true;
    ecount++;
}

void input()
{
    memset(head, -1, sizeof(head));
    ecount = 0;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        a--;
        b--;
        if (hash[a][b])
            continue;
        addedge(a, b);
        addedge(b, a);
    }
}

void dfs(int fa, int u)
{
    vis[u] = true;
    low[u] = dfn[u] = tcount++;
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].v;
        if (v == fa)
            continue;
        if (!vis[v])
            dfs(u, v);
        low[u] = min(low[u], low[v]);
    }
}

int tarjan()
{
    memset(dfn, 0, sizeof(dfn));
    memset(vis, 0, sizeof(vis));
    memset(degree, 0, sizeof(degree));
    tcount = 0;
    dfs(0, 0);
    int ret = 0;
    for (int i = 0; i < n; i++)
        for (int j = head[i]; j != -1; j = edge[j].next)
        {
            int v = edge[j].v;
            if (low[i] != low[v])
                degree[low[i]]++;
        }
    for (int i = 0; i < n; i++)
        if (degree[i] == 1)
            ret++;
    return (ret + 1) / 2;
}

int main()
{
    //freopen("sum.in", "r", stdin);
    input();
    int ans = tarjan();
    printf("%d\n", ans);
    return 0;
}