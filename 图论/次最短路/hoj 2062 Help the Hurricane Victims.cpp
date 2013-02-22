/*

HOJ和POJ这两题都是次短路的问题，但是题目描述和求解方法上有区别。
Help题目描述：
给定无向图，求是否存在次短路。

Help题目分析：
拿到题目最初的想法是用K短路求法（启发式搜索）求次短路。但是第二组数据否定了这种想法。
因为123路径长20，那么对于无向图必然存在12123长为40的次短路。可是题目输出了
“Sorry, no different ways available.”可以想见，这个题目不是简单地求次短路的问题。
题目中有一句很关键的话说----
"Two different shortest ways" means the shortest way and the second shortest one. 
Two ways are different if at least one street in way 1 is not included in way 2 or vice versa.
这句话的重要性是在王教头的指点下才想见的。Help一题中的次短路有一个限制是次短路与最短路至少有
一条边不同。而凡是通过反复访问同一顶点得到的次短路都不符合这一条件。
这是可能会想到，次短路是一条既有一些边与最短路上的边不同，又有重复访问顶点的情况。但可以很容易
证明这样的路径一定不是次短路，设这种结构的路径长为L，那么必然有
L’ = L – cost(loop on the certain vertex)。L’ < L。所以次短路要么重复访问顶点，要么有一些
边与最短路上的边不同。
这样算法就出来了，用Dijkstra求出最短路，然后枚举起点到终点路径上的边，删去，再求一次最短路，
将这些路径长比较一下就会得到题目中要求的次短路。
但是这题数据上有个歧义，就是次短路能不能与最短路大小相等？我最初按照不能相等做，结果WA了两次，
后来改成可以相等，就过了。


Sightseeing题目描述：
求最短路和比最短路大1的路的数量。
YY：这题是zfy0701大牛的图论分类中的一道中等题，个人觉得是属于算法不新，主要靠想的题目。当然也是
综合了最短路个数的计数、次短路的二维dijk求法的一个题目。学大牛向大家推荐一下。
二维dijk的思路是用dist[V][0/1]记录到V点的最短距离和次短距离。用加入距离集合的边去更新
dist[V][0/1]。如果更新dist[V][1]只要像普通的dijk一样去更新，如果要更新dist[V][0]则要去更
新dist[V][1]（很容易想到要更新最短的原来的最短的就变成次短的了）。统计时就是遇到更新时时用加
入集合的点去的cnt去赋值，如果遇到等长的距离的情况，就把加入集合的点的cnt加上。

*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define X 130
#define	INF 1<<30
int map[X][X],dis[X],pre[X],path[X],n,m;
bool use[X];
int dijkstra()		//dijkstra算法求最短路
{
	memset(use,false,sizeof(use));
	for(int i=1;i<=n;i++)
		dis[i] = map[i][1],pre[i] = 1;
	dis[1] = pre[1] = 0;
	use[1] = true;
	int MIN,k;
	for(int i=1;i<n;i++)
	{
		MIN = INF;
		for(int j=2;j<=n;j++)
			if(!use[j]&&dis[j]<MIN)
				MIN = dis[k=j];
		if(MIN==INF)
			return INF;
		if(k==n)
			return dis[n];
		use[k] = true;
		for(int j=2;j<=n;j++)
			if(!use[j]&&dis[j]>dis[k]+map[k][j])	//对便进行松弛操作
			{
				dis[j] = dis[k]+map[k][j];
				pre[j] = k;
			}
	}
	return dis[n];
}
int find_second_min()			//求次最短路，每次删除一条边从而使最短路变成次最短路
{
	for(int i=1;i<=n;i++)
		path[i] = pre[i];
	int ans = INF,temp,t;
	for(int i=n;i!=1;i=path[i])
	{
		temp = map[i][path[i]];	//开始枚举每一条最短路上的边
		map[i][path[i]] = map[path[i]][i] = INF;//把该边改为没有连通的
		t = dijkstra();			//删除最短路上的一条边后，求它的最短路(即次最短路)
		if(t<INF)
			ans = min(t,ans);	//更新答案
		map[i][path[i]] = map[path[i]][i] = temp;//改回来
	}
	return ans;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int x,y,z;
	while(cin>>n>>m,n||m)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				map[i][j] = INF;
		for(int i=0;i<m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			map[x][y] = map[y][x] = z;
		}
		int ans1 = dijkstra();
		if(ans1==INF)
			cout<<"Sorry, no different ways available."<<endl;
		else
		{
			int ans2 = find_second_min();
			if(ans2==INF)
				cout<<"Sorry, no different ways available."<<endl;
			else
				cout<<ans1<<" "<<ans2<<endl;
		}
	}
	return 0;
}