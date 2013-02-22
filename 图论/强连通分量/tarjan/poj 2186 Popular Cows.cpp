#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int E = 50002;
const int V = 10002;

struct node
{
    node *next;
    int v;
    void fun()
    {
        v = 0;
        next = NULL;
    }
}edge[E],*head[E],*tmp;

int dfn[V],low[V],stack[V],father[V],counter[V],n,m,depth,top,bcnt;

bool instack[V],out[V];

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
            low[u] = min(low[u],low[v]);
        }
        else if(instack[v])
            low[u] = min(low[u],dfn[v]);
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
    //memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(counter,0,sizeof(counter));
    memset(out,false,sizeof(out));
    memset(instack,false,sizeof(instack));

    top = bcnt = depth = 0;

    for(int i=1;i<=n;i++)
        if(!low[i])
            tarjan(i);

    for(int i=1;i<=n;i++)
    {
        counter[father[i]]++;
        for(node *p=head[i];p;p=p->next)
            if(father[i]!=father[p->v])
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

    memset(head,NULL,sizeof(head));

    scanf("%d%d",&n,&m);


    for(int i=0;i<=m;i++)
        edge[i].fun();

    tmp = edge;

    int a,b;

    for(int i=0;i<m;i++)
    {
        scanf("%d%d",&a,&b);
        tmp->next = head[a];
        tmp->v = b;
        head[a] = tmp++;
    }

    solve();

    return 0;
}
