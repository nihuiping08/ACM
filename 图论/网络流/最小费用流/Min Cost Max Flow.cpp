/*

题目：
    求最小费用最大流的裸模板

分析：
    每次找到一条最短路，然后记录下每个经过的节点的前驱结点，然后若能够
    到达终点的话，从终点开始往回找到最小流，然后再从终点往回依次更改当
    前每条边的流量以及反向弧，直到不能再找到一条最短路为止，找最短路的
    算法是spfa

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 10005;
const int maxm = 1000005;
const int inf = 1e8;
#define debug puts("here");

int n,m,s,t,cas,ans,cl,aug;
int dis[maxn],pre[maxn],po[maxn];
bool use[maxn];
int q[maxm],head,tail;

struct node
{
    int y,next,f,c;
}edge[maxm];

void add(int x,int y,int f,int c)
{
    edge[++cl].y = y;
    edge[cl].f = f;
    edge[cl].c = c;
    edge[cl].next = po[x];
    po[x] = cl;

    edge[++cl].y = x;
    edge[cl].f = 0;
    edge[cl].c = -c;
    edge[cl].next = po[y];
    po[y] = cl;
}

int spfa()
{
    memset(use,false,sizeof(use));
    for(int i=0;i<=n;i++)
        dis[i] = inf;
    head = tail = 0;
    q[tail++] = s;
    dis[s] = 0;
    pre[s] = 0;
    int x,y;
    while(head<tail)
    {
        x = q[head++];
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next)
        {
            y = edge[i].y;
            if(edge[i].f>0&&edge[i].c+dis[x]<dis[y])
            {
                dis[y] = edge[i].c+dis[x];
                pre[y] = i;
                if(!use[y])
                {
                    q[tail++] = y;
                    use[y] = true;
                }
            }
        }
    }
    if(dis[t]==inf)
        return false;
    aug = inf;
    for(int i=pre[t];i;i=pre[edge[i^1].y])
        aug = min(aug,edge[i].f);
    for(int i=pre[t];i;i=pre[edge[i^1].y])
    {
        edge[i].f -= aug;
        edge[i^1].f += aug;
    }
    ans += dis[t]*aug;
    return true;
}

int main()
{
    freopen("sum.in","r",stdin);
    int ncase,x,y,f,c;
    char str[10];
    cin>>ncase;
    while(ncase--)
    {
        scanf("%s%d",str,&x);
        scanf("%d%d%d%d",&n,&m,&s,&t);

        memset(po,0,sizeof(po));
        cl = 1;

        for(int i=0;i<m;i++)
        {
            scanf("%d%d%d%d",&x,&y,&f,&c);
            add(x,y,f,c);
        }

        ans = 0;
        while(spfa());

        cout<<ans<<endl;
    }
    return 0;
}
