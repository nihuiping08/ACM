/*

题目：
    有n种物品，现给出m种关系，每种关系a,b对应着物品b能够用物品a来换，然后有q个询问(a,b)，
    问物品a能不能换到物品b。

分析：
    如果直接dfs求传递闭包的话，会超时的。我们可以重新建图，使得图中没有环，即把强连通分支
    变成缩点后用邻接表重新建图，然后dfs求传递闭包即可

*/
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 5005;

int dfn[X],father[X],low[X],stack[X],depth,top,bcnt;
int n,m,t;
bool instack[X];
bool map[1005][1005];   //新图中的关系
vector<int> adj[X];     //旧图
vector<int> nadj[X];    //新图

void tarjan(int u)  //tarjan算法求强连通分支
{
    int len,v;
    low[u] = dfn[u] = ++depth;
    stack[++top] = u;
    instack[u] = true;
    len = adj[u].size();
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
    memset(instack,false,sizeof(instack));
    memset(low,0,sizeof(low));
    memset(map,false,sizeof(map));

    for(int i=1;i<=n;i++)
        if(!low[i])
            tarjan(i);
    int len,v;
    for(int u=1;u<=n;u++)   //重新建图
    {
        len = adj[u].size();
        for(int j=0;j<len;j++)
        {
            v = adj[u][j];
            if(father[u]!=father[v])//father记录的是在新图中的顶点号（所在缩点的号码）
                nadj[father[u]].push_back(father[v]);
        }
    }
}

void dfs(int u,int v)   //dfs求传递闭包，若用floyd的话会超时
{
    int len = nadj[v].size();
    for(int i=0;i<len;i++)
        dfs(u,nadj[v][i]);
    map[u][v] = true;
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        for(int i=1;i<=n;i++)   //初始化
        {
            adj[i].clear();
            nadj[i].clear();
        }
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&u,&v);
            adj[u].push_back(v);
        }
        solve();
        for(int i=1;i<=bcnt;i++)    //求传递闭包
            dfs(i,i);

        scanf("%d",&t);
        while(t--)
        {
            scanf("%d%d",&u,&v);
            if(father[u]==father[v])
            {
                printf("Yes\n");
                continue;
            }
            if(map[father[u]][father[v]])
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
    return 0;
}
