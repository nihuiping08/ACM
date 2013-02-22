/*

2011年北京区域赛A题
Qin Shi Huang's National Road System


题目:
    秦始皇想要修公路，使得这n座城市可以互达，题目给出n所城市的二维坐标以及每座城
    市的价值，现在有人可以免费帮助秦始皇修理任意一条公路，现在要想使得比率A/B最大,
    A表示这条公路所在的两座城市的价值，B表示所有的公路长度（不包括这条公路的长度）。

分析：
    想要比率最大，所以A要尽可能大，B尽可能小。要使B尽可能小的话，可以先求的最小生
    成树，然后枚举在最小生成树上的每条边，删除该边后得到的两个点集中分别找到最大价值
    的点（城市），然后更新答案。时间复杂度为O(n^2)。而找两个集合中的点时，我们可以
    通过dfs求得，具体实现请看代码

*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

const int X = 1002;
#define INF 1e12

struct node
{
    int x,y,w;
}p[X];

int n;
double map[X][X];
double dis[X],total,ans;
bool use[X];
int pre[X];     //记录点i的前趋节点

double dist(int x1,int y1,int x2,int y2)    //距离
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void prim() //求最小生成树
{
    memset(pre,0,sizeof(pre));
    total = 0;
    memset(use,false,sizeof(use));
    for(int i=1;i<=n;i++)
        dis[i] = INF;
    dis[1] = 0;
    int k;
    double MIN;
    for(int i=0;i<n;i++)
    {
        MIN = INF;
        for(int j=1;j<=n;j++)
            if(!use[j]&&dis[j]<MIN)
                MIN = dis[k = j];
        use[k] = true;
        total += MIN;
        for(int j=1;j<=n;j++)
            if(!use[j]&&dis[j]>map[k][j])
                dis[j] = map[k][j],pre[j] = k;
    }
}

void dfs(int i) //dfs，通过对他的后趋点进行深搜，找到同一集合中所有的点
{
    use[i] = true;
    for(int j=1;j<=n;j++)
        if(!use[j]&&pre[j]==i)
            dfs(j);
}

void solve()
{
    double temp;
    ans = 0;
    int a,b;
    for(int i=1;i<=n;i++)   //枚举每条边
    {
        if(pre[i]==0)
            continue;
        temp = total-map[i][pre[i]];    //删除边i,pre[i]
        memset(use,false,sizeof(use));
        dfs(i);
        a = b = 0;
        for(int j=1;j<=n;j++)
        {
            if(use[j]&&j!=pre[i])   //与pre[i]同一集合中的点，找到最大的价值城市
                a = max(a,p[j].w);
            else if(!use[j]&&j!=i)    //与i同一集合中的点。。。
                b = max(b,p[j].w);
        }
        ans = max(ans,(a+b)/temp);
    }
    printf("%.2lf\n",ans);
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int t;
    cin>>t;
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].w);
            for(int j=i;j>=1;j--)   //预处理出所有点与点之间的距离
                map[i][j] = map[j][i] = dist(p[i].x,p[i].y,p[j].x,p[j].y);
        }
        prim();
        solve();
    }
    return 0;
}
