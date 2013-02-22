#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

const int V = 20005;
const int E = 50005;

int father[V],dfn[V],low[V],stack[V],n,m,depth,bcnt,top;
int in[V],out[V];
int from[E],to[E];
bool instack[V];
vector<int> edge[V];

void tarjan(int u)
{
    low[u] = dfn[u] = ++depth;
    instack[u] = true;
    stack[++top] = u;
    int v;
    int len = edge[u].size();
    for(int i=0;i<len;i++)
    {
        v = edge[u][i];
        if(!low[v])
        {
            tarjan(v);
            low[u] = min(low[u],low[v]);
        }
        else if(instack[v])
            low[u] = min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        bcnt++;
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
    memset(low,0,sizeof(low));
    memset(instack,false,sizeof(instack));
    memset(in,0,sizeof(in));
    memset(out,0,sizeof(out));
    depth = top = bcnt = 0;

    for(int i=1;i<=n;i++)
        if(!low[i])
            tarjan(i);
    if(bcnt==1)
    {
        printf("0\n");
        return;
    }
    int u,v;
    for(int i=0;i<m;i++)
    {
        u = father[from[i]];
        v = father[to[i]];
        if(u!=v)
        {
            in[u]++;
            out[v]++;
        }
    }
    int co = 0,ci = 0;
    for(int i=1;i<=bcnt;i++)
    {
        if(in[i]==0)
            ci++;
        if(out[i]==0)
            co++;
    }
    printf("%d\n",max(co,ci));
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int t,u,v;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            edge[i].clear();
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&u,&v);
            from[i] = u;
            to[i] = v;
            edge[u].push_back(v);
        }
        solve();
    }
    return 0;
}
