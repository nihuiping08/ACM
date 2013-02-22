/*

题目：
	求最短路和次短路是不是一样长度

分析：
	可以用prim求出最小生成树，接着枚举每条不出现在最小生成树中边，找一条
	不在最小生成树中的边（能走通）去替换最小生成树中的一条边，然后判断是不是与
	之前求出的最小值相等

*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define X 105
#define INF 10000000
int map[X][X],path[X][X],dis[X],pre[X],n,m;
bool use[X],visit[X][X];
int prim()
{
	memset(use,false,sizeof(use));		//在prim中记录是否用过
	memset(visit,false,sizeof(visit));	//表示边是否出现在最小生成树中
	memset(pre,0,sizeof(pre));			//前趋顶点
	memset(path,0,sizeof(path));		//记录最小生成树中任意两点之间最大边的值

	for(int i=2;i<=n;i++)
		dis[i] = INF;
	dis[1] = 0;
	int MIN,k,ans = 0;

	for(int i=0;i<n;i++)
	{
		MIN = INF;
		for(int j=1;j<=n;j++)
			if(!use[j]&&dis[j]<MIN)
				MIN = dis[k=j];

		if(MIN==INF)
			return INF;

		////////////////////////////////////////////多的部分
		int p = pre[k];
		path[p][k] = MIN;
		visit[p][k] = visit[k][p] = true;//是所求最小生成树中，标记为true  

		for(int j=1;j<=n;j++)
			if(use[j])	//更新所有已在最小生成树中的点到u的max_val[i][u]  
				//path[j][k] = path[j][p]>path[p][k]?path[j][p]:path[p][k];
				path[j][k] = max(path[j][p],path[p][k]);
				//由于前趋肯定已经被更新，所以只需要j到p与p到k比较即可
		//////////////////////////////////////////

		use[k] = true;
		ans += MIN;
		for(int j=1;j<=n;j++)
			if(!use[j]&&map[k][j]<dis[j])
				dis[j] = map[k][j],pre[j] = k;//如果k能把dis[j]更新，则k是j的pre  
	}
	return ans;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t,x,y,z;
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				map[i][j] = INF;
		while(m--)
		{
			scanf("%d%d%d",&x,&y,&z);
			map[x][y] = map[y][x] = z;
		}
		int ans = prim();	//先求出最小生成树
		bool flag = true;
		for(int i=1;i<=n&&flag;i++)
			for(int j=1;j<=n&&flag;j++)
				if(!visit[i][j]&&map[i][j]!=INF)//找一条不在最小生成树中的边（能走通）去替换最小生成树中的一条边  
					if((ans+map[i][j]-path[i][j])==ans)
						flag = false;
		if(flag)
			cout<<ans<<endl;
		else
			cout<<"Not Unique!"<<endl;
	}
	return 0;
}