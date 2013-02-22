/*



*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 20005;
const int maxm = 2000005;

int head[maxn],a[maxm],n,m,cl;
bool instack[maxn];
int dfn[maxn],low[maxn],stack[maxn],father[maxn],depth,bcnt,top;

struct node
{
    int y,next;
}p[maxm];

void dfs(int x)
{
    int y;
    dfn[x] = low[x] = ++depth;
    instack[x] = true;
    stack[++top] = x;
    for(int i=head[x];i!=-1;i=p[i].next)
    {
        y = p[i].y;
        if(!dfn[y])
        {
            dfs(y);
            low[x] = min(low[x],low[y]);
        }
        else if(instack[y])
            low[x] = min(low[x],dfn[y]);
    }
    if(dfn[x]==low[x])
    {
        bcnt++;
        do
        {
            y = stack[top--];
            instack[y] = false;
            father[y] = bcnt;
        }while(x!=y);
    }
}

void tarjan()
{
    memset(dfn,0,sizeof(dfn));
    memset(instack,false,sizeof(instack));
    depth = top = bcnt = 0;
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            dfs(i);
}

void add(int x,int y)
{
    p[++cl].y = y;
    p[cl].next = head[x];
    head[x] = cl;
}

void solve()
{
    int y;
    for(int i=1;i<=m;i++)
    {
        top = 0;
        for(int j=head[i];j!=-1;j=p[j].next)
        {
            y = p[j].y;
            if(father[y]==father[i])
                a[top++] = y-m;
        }
        printf("%d",top);
        sort(a,a+top);
        for(int j=0;j<top;j++)
            printf(" %d",a[j]);
        cout<<endl;
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>m)
    {
        n = m*2;
        int x,y;
        cl = 1;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=m;i++)
        {
            scanf("%d",&y);
            while(y--)
            {
                scanf("%d",&x);
                add(i,x+m);
            }
        }
        for(int i=1;i<=m;i++)
        {
            scanf("%d",&x);
            add(x+m,i);
        }
        tarjan();
        solve();
    }
    return 0;
}
