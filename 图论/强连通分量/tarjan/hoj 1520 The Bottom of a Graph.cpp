#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 15005;

int dfn[X],low[X],father[X],stack[X],bcnt,top,depth;
int counter[X],n,m;
bool instack[X];
vector<int> adj[X];

void tarjan(int u)
{
    low[u] = dfn[u] = ++depth;
    instack[u] = true;
    stack[++top] = u;
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
    depth = top = bcnt = 0;
    memset(low,0,sizeof(low));
    memset(instack,false,sizeof(instack));
    memset(counter,0,sizeof(counter));

    for(int i=1;i<=n;i++)
        if(!low[i])
            tarjan(i);

    int len;
    for(int i=1;i<=n;i++)
    {
        len = adj[i].size();
        for(int j=0;j<len;j++)
            if(father[i]!=father[adj[i][j]])
                counter[father[i]]++;
    }
    bool flag = false;
    for(int i=1;i<=n;i++)
        if(!counter[father[i]])
        {
            if(flag)
                printf(" ");
            else
                flag = true;
            printf("%d",i);
        }
    printf("\n");
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int u,v;
    while(scanf("%d",&n),n)
    {
        scanf("%d",&m);
        for(int i=1;i<=n;i++)
            adj[i].clear();
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&u,&v);
            adj[u].push_back(v);
        }
        solve();
    }

    return 0;
}
