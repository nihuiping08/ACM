/*

找到强连通分量变成缩点后求给出出度为0的所有点
以下用tarjan算法做，第一个是用结构体的邻接链表来做，第二个使用的是vector作为邻接链表

*/
#include <cstdio>
#include <cstring>

const int X = 15002;

int dfn[X],low[X],stack[X],father[X],depth,top,bcnt;
int counter[X],n,m;
bool instack[X];

struct node
{
    int v;
    node *next;
    void fun()
    {
        v = 0;
        next = NULL;
    }
}edge[X],*head[X],*tmp;

void tarjan(int u)
{
    int v;
    dfn[u] = low[u] = ++depth;
    stack[++top] = u;
    instack[u] = true;

    for(node *p=head[u];p;p=p->next)
    {
        v = p->v;
        if(!low[v])
        {
            tarjan(v);
            if(low[v]<low[u])
                low[u] = low[v];
        }
        else if(instack[v]&&low[u]>dfn[v])
            low[u] = dfn[v];
    }
    if(low[u]==dfn[u])
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
    top = depth = bcnt = 0;
    memset(instack,false,sizeof(instack));
    memset(low,0,sizeof(low));
    memset(counter,0,sizeof(counter));

    for(int i=1;i<=n;i++)
        if(!low[i])
            tarjan(i);

    for(int i=1;i<=n;i++)
        for(node *p=head[i];p;p=p->next)
            if(father[i]!=father[p->v])
                counter[father[i]]++;
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
        memset(head,NULL,sizeof(head));

        for(int i=0;i<m;i++)
            edge[i].fun();
        tmp = edge;
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&u,&v);
            tmp->next = head[u];
            tmp->v = v;
            head[u] = tmp++;
        }
        solve();
    }
    return 0;
}
/*

vector作为邻接链表

*/
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
