/*

题目：
    现给出各位选手的能力比较并给出自己的朋友的参赛号码，如何组织比赛使得自己的朋友能够获胜

分析：
    各选手能力比较可以构造一个有向图，而想要使得自己的朋友要赢得比赛，所以他的所在的连通块
    必定是入度为0的（假设建图时是以能力大的人作为边的起点）。所以题目可以转换为先建图，然后
    再找连通块求缩点，然后判断该缩点是否入度为0，若有朋友在该连通块中，即可判断可以组织这样
    的一场比赛。而判断朋友在不在该连通块中，可以先求到所有的入度为0的连通块用数组置为true，
    然后直接把所有朋友的所在的连通块置为false,若所有的连通块中只要还有true的连通块，就可判断
    不能组织这样的一场比赛

*/
#include <cstdio>
#include <cstring>

const int X = 100005;

int dfn[X],low[X],stack[X],deg[X],father[X],depth,top,bcnt;
int f[X],fri,n,m;
bool use[X],instack[X];

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
    memset(instack,false,sizeof(instack));
    memset(low,0,sizeof(low));
    memset(deg,0,sizeof(deg));
    depth = bcnt = top = 0;

    for(int i=1;i<=n;i++)
        if(!low[i])
            tarjan(i);

    for(int i=1;i<=n;i++)
        for(node *p=head[i];p;p=p->next)
            if(father[i]!=father[p->v])
                deg[father[p->v]]++;

    memset(use,false,sizeof(use));
    for(int i=1;i<=bcnt;i++)
        if(!deg[i])
            use[i] = true;

    for(int i=0;i<fri;i++)
        use[father[f[i]]] = false;

    bool flag = true;
    for(int i=1;i<=bcnt;i++)
        if(use[i])
        {
            flag = false;
            break;
        }
    flag?printf("yes\n"):printf("no\n");
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(scanf("%d%d%d",&n,&fri,&m),n||m||fri)
    {
        for(int i=0;i<fri;i++)
            scanf("%d",&f[i]);
        memset(head,NULL,sizeof(head));

        for(int i=0;i<m;i++)
            edge[i].fun();
        tmp = edge;
        int u,v;
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
