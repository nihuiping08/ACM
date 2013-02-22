/*

题目：
    给出区间[ai,bi]，他与全集的交集的个数为ci，问全集中至少有多少个元素

分析：
    用数组dist[i]表示从0到i与全集的交集的个数；
    输入数据即可转化为：dist[b+1]-dist[a]>=z      =>    dist[a]-dist[b+1]<=-z
    根据实际情况还有两个约束条件：
    dist[i+1]-dist[i]<=1
    dist[i+1]-dist[i]>=0    =>   dist[i]-dist[i]+1<=0
    于是可以建图，SPFA。
    最后输出dist[max]-dist[min]即可（max与min 为输入数据出现的最大点和最小点）

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int X = 50005;
const int inf = 1e9;
#define debug puts("here");

int dis[X],head[X],top,n;
bool use[X];
int mx,mi;

struct node
{
    int y,w,next;
}p[X*3];

void spfa(int src)
{
    memset(use,false,sizeof(use));
    for(int i=0;i<=mx;i++)
        dis[i] = inf;
    queue<int> q;
    use[src] = true;
    dis[src] = 0;
    q.push(src);
    int x,y,w;
    while(!q.empty())
    {
        x = q.front();
        q.pop();
        use[x] = false;
        for(int i=head[x];i!=-1;i=p[i].next)
        {
            y = p[i].y;
            w = p[i].w+dis[x];
            if(dis[y]>w)
            {
                dis[y] = w;
                if(!use[y])
                {
                    use[y] = true;
                    q.push(y);
                }
            }
        }
    }
    printf("%d\n",dis[mx]-dis[mi]);
}

void add(int x,int y,int w)
{
    p[top].y = y;
    p[top].w = w;
    p[top].next = head[x];
    head[x] = top++;
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n)
    {
        int x,y,z;
        memset(head,-1,sizeof(head));
        top = 0;
        mx = -inf;
        mi = inf;
        for(int i=0;i<n;i++)
        {
            scanf("%d%d%d",&x,&y,&z);
            y++;
            add(y,x,-z);
            mi = min(mi,x);
            mx = max(mx,y);
        }
        for(int i=1;i<=mx;i++)
        {
            add(i,i-1,0);
            add(i-1,i,1);
        }
        spfa(mx);
    }
    return 0;
}
