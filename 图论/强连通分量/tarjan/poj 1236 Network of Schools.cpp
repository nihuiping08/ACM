/*



*/
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 305;

int dfn[X],low[X],stack[X],father[X],depth,top,bcnt;
int id[X],od[X],n;
bool instack[X];
vector<int> adj[X];

void tarjan(int u)
{
    low[u] = dfn[u] = ++depth;
    stack[++top] = u;
    instack[u] = true;
    int v,len = adj[u].size();
    for(int i=0;i<len;i++)
    {
        v = adj[u][i];
        if(!low[v])
        {
            tarjan(v);
            low[u] = min(low[u],low[v]);
        }
        else if(instack[v])
            low[u] = min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u])
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
    memset(instack,false,sizeof(instack));
    memset(low,0,sizeof(low));
    memset(id,0,sizeof(id));
    memset(od,0,sizeof(od));
    top = depth = bcnt = 0;

    for(int i=1;i<=n;i++)
        if(!low[i])
            tarjan(i);

    int v,len;
    for(int u=1;u<=n;u++)
    {
        len = adj[u].size();
        for(int j=0;j<len;j++)
        {
            v = adj[u][j];
            if(father[u]!=father[v])
            {
                od[father[u]]++;
                id[father[v]]++;
            }
        }
    }
    if(bcnt==1)
    {
        printf("1\n0\n");
        return;
    }
    int ci = 0;
    int co = 0;
    for(int i=1;i<=bcnt;i++)
    {
        if(!id[i])
          ci++;
        if(!od[i])
            co++;
    }
    printf("%d\n%d\n",ci,max(co,ci));
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int v;
    scanf("%d",&n);
    for(int u=1;u<=n;u++)
        while(scanf("%d",&v),v)
            adj[u].push_back(v);
    solve();

    return 0;
}
