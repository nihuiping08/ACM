#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

const int V = 10005;

int dfn[V],low[V],stack[V],father[V],counter[V],n,m,depth,top,bcnt;
bool instack[V],out[V];
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
    memset(out,false,sizeof(out));
    memset(counter,0,sizeof(counter));
    memset(instack,false,sizeof(instack));
    memset(low,0,sizeof(low));
    top = depth = bcnt = 0;

    for(int i=1;i<=n;i++)
        if(!low[i])
            tarjan(i);

    int len;
    for(int i=1;i<=n;i++)
    {
        counter[father[i]]++;
        len = edge[i].size();
        for(int j=0;j<len;j++)
            if(father[i]!=father[edge[i][j]])
                out[father[i]] = true;
    }

    int num = 0,ans;
    for(int i=1;i<=bcnt;i++)
        if(!out[i])
        {
            num++;
            ans = counter[i];
        }
    if(num==1)
        printf("%d\n",ans);
    else
        printf("0\n");
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    scanf("%d%d",&n,&m);
    int u,v;
    for(int i=0;i<m;i++)
    {
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
    }
    solve();

    return 0;
}
