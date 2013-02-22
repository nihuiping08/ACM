#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int X = 105;

int in[X],out[X],order[X],father[X];
int n,m,scc,bcnt;
bool use[X];
bool g[X][X],gr[X][X];

void init()
{
    scanf("%d",&n);

    scc = bcnt = 0;
    memset(use,false,sizeof(use));
    memset(g,false,sizeof(g));
    memset(gr,false,sizeof(gr));
    memset(in,0,sizeof(in));
    memset(out,0,sizeof(out));

    for(int i=1;i<=n;i++)
    {
        while(scanf("%d",&m),m)
        {
            g[i][m] = true;
            gr[m][i] = true;
        }
    }
}

void dfs(int v)
{
    use[v] = true;
    for(int i=1;i<=n;i++)
        if(!use[i]&&g[v][i])
            dfs(i);
    order[++bcnt] = v;
}

void rdfs(int v)
{
    use[v] = true;
    father[v] = scc;
    for(int i=1;i<=n;i++)
        if(!use[i]&&gr[v][i])
            rdfs(i);
}

void korasaju()
{
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
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(g[i][j]&&father[i]!=father[j])
            {
                out[father[i]]++;
                in[father[j]]++;
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

    init();
    korasaju();
    solve();

    return 0;
}
