/*

2-SAT问题一般指这样的问题：2n个顶点可以分为n组，每组2个顶点，且这两个
顶点只能选择其中一个如果根据限制条件，选了顶点a后，必须选择b，则添加
一条有向边(a,b)
这题中，n对夫妻(包括新郎和新娘）恰好可以代表n组点，女的标为0，2...男
的标为1,3...每对夫妻，只能选一个坐在新娘的对面,若选中一个点表示该点在
新娘的对面，则对于特殊关系x,y，添加边(x,~y),(y,~x)最后添加边(0,1)

*/
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int X = 200;
#define debug puts("here");

int father[X],stack[X],dfn[X],low[X];
int bcnt,top,depth,n,m,qq;
int head[X];
int col[X],ind[X],con[X];
bool map[X][X];
bool instack[X];

struct node
{
    int y,next;
}p[X];

void dfs(int u)
{
    instack[u] = true;
    stack[++top] = u;
    low[u] = dfn[u] = ++depth;
    int v;
    for(int i=head[u];i!=-1;i=p[i].next)
    {
        v = p[i].y;
        if(!low[v])
        {
            dfs(v);
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

void tarjan()
{
    memset(instack,false,sizeof(instack));
    memset(low,0,sizeof(low));
    depth = top = bcnt = 0;
    for(int i=0;i<(n<<1);i++)
        if(!low[i])
            dfs(i);
}

void build_dag()
{
    int y;
    for(int i=0;i<(n<<1);i++)
        for(int j=head[i];j!=-1;j=p[j].next)
        {
            y = p[j].y;
            if(father[i]!=father[y])
                map[father[y]][father[i]] = true;
        }
    for(int i=1;i<=bcnt;i++)
        for(int j=1;j<=bcnt;j++)
            if(map[i][j])
                ind[j]++;
}

void topsort()
{
    for(int i=1;i<=bcnt;i++)
        if(ind[i]==0)
            stack[++top] = i;
    int x;
    while(top)
    {
        x = stack[top--];
        if(!col[x])
        {
            col[x] = 1;
            col[con[x]] = 2;
        }
        for(int i=1;i<=bcnt;i++)
            if(map[x][i])
            {
                if(--ind[i]==0)
                    stack[++top] = i;
            }
    }
}

void solve()
{
    for(int i=0;i<n;i++)
    {
        if(father[i<<1]==father[i<<1|1])
        {
            puts("bad luck");
            return;
        }
        con[father[i<<1]] = father[i<<1|1];
        con[father[i<<1|1]] = father[i<<1];
    }

    memset(map,false,sizeof(map));
    memset(ind,0,sizeof(ind));
    build_dag();

    memset(col,0,sizeof(col));
    top = 0;
    topsort();

    for(int i=2;i<(n<<1);i+=2)
    {
        if(i!=2)
            printf(" ");
        if(col[father[i]]==col[father[0]])
            printf("%dw",i>>1);
        else
            printf("%dh",i>>1);
    }
    cout<<endl;
}

void add(int x,int y)
{
    p[qq].y = y;
    p[qq].next = head[x];
    head[x] = qq++;
}

void input()
{
    qq = 0;
    memset(head,-1,sizeof(head));

    char s,str;
    int x,y,xx,yy;
    while(m--)
    {
        scanf("%d%c %d%c",&x,&s,&y,&str);
        if(s=='h')
        {
            xx = x<<1;  //女的编号为0,2,4...
            x = x<<1|1; //男的编号为1,3,5...
        }
        else
        {
            xx = x<<1|1;
            x = x<<1;
        }
        if(str=='h')
        {
            yy = y<<1;
            y = y<<1|1;
        }
        else
        {
            yy = y<<1|1;
            y = y<<1;
        }
        add(x,yy);
        add(y,xx);
    }
    add(0,1);
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n>>m,n||m)
    {
        input();
        tarjan();
        solve();
    }
    return 0;
}
