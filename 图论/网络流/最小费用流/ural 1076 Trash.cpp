/*

题目：
    题目大意是给定N个垃圾桶，每个垃圾桶内装有N种数量不同的垃圾，现你把
    垃圾分类，要求每个垃圾桶装一种垃圾，移动一个单位的垃圾消耗1的代价，
    求最小的移动代价，使得完成垃圾分类。

分析：
    这个问题可以构建出二分图的最佳匹配的模型。把原有的垃圾桶看作X集合
    中的顶点，垃圾种类看作Y集合中的顶点，边(a,b)表示a垃圾桶装b类垃圾，
    所需移动的代价。求二分图的最小权完备匹配，匹配边权值之和最小值就
    是要求的结果。
    为了能够使用求最大权匹配的KM算法，只需把所有边的权值取相反数，求最
    大权匹配，结果再取相反数即可。

    另外可以用最小费用最大流的算法来做，给X部连上一个源点，并且每条边的
    流量为1，费用为0，对于Y部同样连上一个汇点，每条有向边的流量为1，费用
    为0，原图中的边的流量均为1，费用均为原来的相反数，最后是最小费用加上
    总的权值

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 1005;
const int maxm = 100005;
const int inf = 1e8;
#define debug puts("here");

int po[maxn],pre[maxn],dis[maxn];
bool use[maxn];
int head,tail,q[maxm];
int n,m,s,t,cl,ans;

struct node
{
    int y,f,c,next;
}edge[maxm];

void add(int x,int y,int f,int c)
{
    edge[++cl].y = y;
    edge[cl].f = f;
    edge[cl].c = c;
    edge[cl].next = po[x];
    po[x] = cl;

    edge[++cl].y = x;
    edge[cl].c = -c;
    edge[cl].f = 0;
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
    int aug = inf;
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
    int x;
    while(cin>>n)
    {
        m = n;
        n = n*2+2;
        s = m<<1|1;
        t = s+1;
        cl = 1;
        int sum = 0;
        memset(po,0,sizeof(po));

        for(int i=1;i<=m;i++)
            for(int j=1;j<=m;j++)
            {
                scanf("%d",&x);
                sum += x;
                add(i,j+m,1,-x);
            }
        for(int i=1;i<=m;i++)
            add(s,i,1,0);
        for(int j=1;j<=m;j++)
            add(j+m,t,1,0);

        ans = 0;
        while(spfa());

        cout<<sum+ans<<endl;
    }
    return 0;
}
