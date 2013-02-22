/*

题目：
    测试最短路的SPFA模板题

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 300005;
const int inf = 1e9;
const int maxn = 1000005;

int head[X],n,m;
int dis[X],q[maxn];
bool use[X];

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
    if(dis[end]==inf)
    {
        puts("-1");
        return;
    }
    printf("%d\n",dis[end]);
}

int main()
{
    freopen("sum.in","r",stdin);
    int x,y,z;
    while(cin>>n>>m)
    {
        memset(head,-1,sizeof(head));
        for(int i=0;i<m;i++)
        {
            scanf("%d%d%d",&x,&y,&z);
            p[i].y = y;
            p[i].w = z;
            p[i].next = head[x];
            head[x] = i;
        }
        scanf("%d%d",&x,&y);
        spfa(x,y);
    }
    return 0;
}
