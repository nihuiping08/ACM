#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 100005;
const int inf = 1e9*2;
const int maxn = 1000005;

int head[X],n,m;
int dis[X],q[maxn];
bool use[X];
int cl;

struct node
{
    int y,w,next;
}p[maxn];

void spfa(int src,int end)
{
    memset(use,false,sizeof(use));
    for(int i=1;i<=n;i++)
        dis[i] = inf;
    dis[src] = 0;
    use[src] = true;
    int h = 0,t = 1;
    q[0] = src;
    int x,y;
    while(h<t)
    {
        x = q[h++];
        use[x] = false;
        for(int i=head[x];i!=-1;i=p[i].next)
        {
            y = p[i].y;
            if(dis[y]-p[i].w>dis[x])
            {
                dis[y] = dis[x]+p[i].w;
                if(!use[y])
                {
                    use[y] = true;
                    q[t++] = y;
                }
            }
        }
    }
    printf("%d\n",dis[end]);
}

void add(int x,int y,int z)
{
    p[++cl].y = y;
    p[cl].w = z;
    p[cl].next = head[x];
    head[x] = cl;

    p[++cl].y = x;
    p[cl].w = z;
    p[cl].next = head[y];
    head[y] = cl;
}

int main()
{
    freopen("sum.in","r",stdin);
    int x,y,z;
    int ncase;
    cin>>ncase;
    while(ncase--)
    {
        cin>>n>>m;
        memset(head,-1,sizeof(head));
        cl = 0;
        for(int i=1;i<n;i++)
        {
            scanf("%d%d%d",&x,&y,&z);
            add(x,y,z);
        }
        while(m--)
        {
            scanf("%d%d",&x,&y);
            spfa(x,y);
        }
    }
    return 0;
}
