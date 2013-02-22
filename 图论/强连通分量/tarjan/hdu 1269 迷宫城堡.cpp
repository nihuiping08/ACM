/*

题目：
    求图中的任意两顶点是否两两互达

分析：
    tanjan算法求得缩点的个数，判断是否为一即可

*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

const int V = 100005;

vector<int> adj[V];

int dfn[V],stack[V],low[V],bcnt,depth,top;
bool instack[V];
int n,m;
//int father[V];

void tarjan(int u)
{
    instack[u] = true;
    stack[++top] = u;
    low[u] = dfn[u] = ++depth;
    int len = adj[u].size();
    int v;
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
            //father[v] = bcnt;
        }while(u!=v);
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int x,y;
    while(scanf("%d%d",&n,&m),n||m)
    {
        for(int i=1;i<=n;i++)
            adj[i].clear();
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&x,&y);
            adj[x].push_back(y);
        }
        memset(instack,false,sizeof(instack));
        memset(low,0,sizeof(low));
        bcnt = depth = top = 0;
        for(int i=1;i<=n;i++)
            if(!low[i])
                tarjan(i);
        if(bcnt==1)
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
    }
    return 0;
}
