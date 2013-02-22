/*
#include <iostream>
#include <cstdio>
using namespace std;
#define X 150005
#define INF 0xfffffff
int dis[30005],n,m;
struct node
{
    int x,y,w;
}p[X];
void ballman_ford()
{
    for(int i=1;i<=n;i++)
        dis[i] = INF;
    dis[1] = 0;
    int x,y;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            x = p[j].x;
			y = p[j].y;
            dis[y] = min(dis[y],dis[x]+p[j].w);
			//对x,y进行松弛操作，即由起点经过x再到y与不经过x到达y
		}
    }
    cout<<dis[n]<<endl;
}
void add(int i,int x,int y,int w)
{
    p[i].x = x;
    p[i].y = y;
    p[i].w = w;
}
int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int x,y,w;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&x,&y,&w);
            add(i,x,y,w);
        }
        ballman_ford();
    }
    return 0;
}
*/
/*
 *
 * 单源最短路算法SPFA,时间复杂度O(kE),k在一般情况下不大于2,对于每个顶点使用可以在O(VE)的时间内算出每对节点之间的最短路
 * 使用了队列,对于任意在队列中的点连着的点进行松弛,同时将不在队列中的连着的点入队,直到队空则算法结束,最短路求出
 * SPFA是Bellman-Ford的优化版,可以处理有负权边的情况
 * 对于负环,我们可以证明每个点入队次数不会超过V,所以我们可以记录每个点的入队次数,如果超过V则表示其出现负环,算法结束
 * 由于要对点的每一条边进行枚举,故采用邻接表时时间复杂度为O(kE),采用矩阵时时间复杂度为O(kV^2)
 
#include<cstdio>
#include<vector>
#include<queue>
#define MAXV 10000
#define INF 1000000000 //此处建议不要过大或过小,过大易导致运算时溢出,过小可能会被判定为真正的距离
 
using std::vector;
using std::queue;
 
struct Edge{
	int v; //边权
	int to; //连接的点
};
 
vector<Edge> e[MAXV]; //由于一般情况下E<<V*V,故在此选用了vector动态数组存储,也可以使用链表存储
int dist[MAXV]; //存储到原点0的距离,可以开二维数组存储每对节点之间的距离
int cnt[MAXV]; //记录入队次数,超过V则退出
queue<int> buff; //队列,用于存储在SPFA算法中的需要松弛的节点
bool done[MAXV]; //用于判断该节点是否已经在队列中
int V; //节点数
int E; //边数
 
bool spfa(const int st){ //返回值:TRUE为找到最短路返回,FALSE表示出现负环退出
	for(int i=0;i<V;i++){ //初始化:将除了原点st的距离外的所有点到st的距离均赋上一个极大值
		if(i==st){
			dist[st]=0; //原点距离为0;
			continue;
		}
		dist[i]=INF; //非原点距离无穷大
	}
	buff.push(st); //原点入队
	done[st]=1; //标记原点已经入队
	cnt[st]=1; //修改入队次数为1
	while(!buff.empty()){ //队列非空,需要继续松弛
		int tmp=buff.front(); //取出队首元素
		for(int i=0;i<(int)e[tmp].size();i++){ //枚举该边连接的每一条边
			Edge *t=&e[tmp][i]; //由于vector的寻址速度较慢,故在此进行一次优化
			if(dist[tmp]+(*t).v<dist[(*t).to]){ //更改后距离更短,进行松弛操作
				dist[(*t).to]=dist[tmp]+(*t).v; //更改边权值
				if(!done[(*t).to]){ //没有入队,则将其入队
					buff.push((*t).to); //将节点压入队列
					done[(*t).to]=1; //标记节点已经入队
					cnt[(*t).to]=1; //节点入队次数自增
					if(cnt[(*t).to]>V){ //已经超过V次,出现负环
						while(!buff.empty())buff.pop(); //清空队列,释放内存
						return false; //返回FALSE
					}
				}
			}
		}
		buff.pop();//弹出队首节点
		done[tmp]=0;//将队首节点标记为未入队
	}
	return true; //返回TRUE
} //算法结束
 
int main(){ //主函数
	scanf("%d%d",&V,&E); //读入点数和边数
	for(int i=0,x,y,l;i<E;i++){
		scanf("%d%d%d",&x,&y,&l); //读入x,y,l表示从x->y有一条有向边长度为l
		Edge tmp; //设置一个临时变量,以便存入vector
		tmp.v=l; //设置边权
		tmp.to=y; //设置连接节点
		e[x].push_back(tmp); //将这条边压入x的表中
	}
	if(!spfa(0)){ //出现负环
		printf("出现负环,最短路不存在\n");
	}else{ //存在最短路
		printf("节点0到节点%d的最短距离为%d",V-1,dist[V-1]);
	}
	return 0;
}
*/
#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
using namespace std;
#define X 30005
struct node
{
	int x,y,w,next;
}p[X*5];
int dis[X],link[X],n,m;
bool use[X];
void spfa()
{
	stack<int> s;
	memset(use,false,sizeof(use));
	memset(dis,0x7f,sizeof(dis));
	dis[1] = 0;
	s.push(1);
	int k,h;
	while(!s.empty())
	{
		h = s.top();
		s.pop();
		use[h] = false;
		k = link[h];
		while(k)
		{
			if(dis[p[k].y]>dis[h]+p[k].w)
			{
				dis[p[k].y] = dis[h]+p[k].w;
				if(!use[p[k].y])
				{
					use[p[k].y] = true;
					s.push(p[k].y);
				}
			}
			k = p[k].next;
		}
	}
	cout<<dis[n]<<endl;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	while(cin>>n>>m)
	{
		memset(link,0,sizeof(link));
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].w);
			p[i].next = link[p[i].x];
			link[p[i].x] = i;
		}
		spfa();
	}
	return 0;
}