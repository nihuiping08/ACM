#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int X = 105;

vector<int> adj[X];
vector<int> radj[X];
int in[X],out[X];
int father[X],order[X],scc,bcnt;
int n,m;
bool use[X];

void init()
{
    for(int i=1;i<=n;i++)
    {
        while(scanf("%d",&m),m)
        {
            adj[i].push_back(m);
            radj[m].push_back(i);
        }
    }
}

void dfs(int u)
{
    use[u] = true;
    int len = adj[u].size();
    int v;
    for(int i=0;i<len;i++)
    {
        v = adj[u][i];
        if(!use[v])
            dfs(v);
    }
    order[++bcnt] = u;
}

void rdfs(int u)
{
    int v;
    int len = radj[u].size();
    use[u] = true;
    father[u] = scc;
    for(int i=0;i<len;i++)
    {
        v = radj[u][i];
        if(!use[v])
            rdfs(v);
    }
}

void korasaju()
{
    bcnt = scc = 0;
    memset(use,false,sizeof(use));
    for(int i=1;i<=n;i++)
        if(!use[i])
            dfs(i);
    memset(use,false,sizeof(use));
    for(int i=n;i;i--)
        if(!use[order[i]])
        {
            scc++;
            rdfs(order[i]);
        }
}

void solve()
{
    if(scc==1)
    {
        printf("1\n0\n");
        return;
    }
    memset(in,0,sizeof(in));
    memset(out,0,sizeof(out));
    int len,v;
    for(int u=1;u<=n;u++)
    {
        len = adj[u].size();
        for(int j=0;j<len;j++)
        {
            v = adj[u][j];
            if(father[u]!=father[v])
            {
                in[father[v]]++;
                out[father[u]]++;
            }
        }
    }
    int co = 0,ci = 0;
    for(int i=1;i<=scc;i++)
    {
        if(!in[i])
            ci++;
        if(!out[i])
            co++;
    }
    printf("%d\n%d\n",ci,max(ci,co));
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    scanf("%d",&n);
    init();
    korasaju();
    solve();
    return 0;
}
