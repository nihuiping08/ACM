/*

题目：
	空降兵要降落在村庄上，伞兵可以在任何路口着陆，也可以沿着单向街道的方向行走以到达另一个路口。
	凡是伞兵走过的路口就可以看成被你占领。用最少的伞兵占领这个城镇所有的路口。

分析：
	在P * P 的图中找一些边，使得这些边能够覆盖所有的顶点，且任一顶点都且与一条边相连。因为
	求的是最小路径覆盖问题，最小路径覆盖 = |P| - 最大匹配数，P为图上的顶点集，所以转化为求
	二分图的最大匹配。另外因为恰好有一个出发点一个结束点，恰好构成一个X部和Y部

*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 122
int ym[X],n,m;
bool g[X][X],use[X];
bool dfs(int u)
{
	for(int v=1;v<=n;v++)
		if(g[u][v]&&!use[v])
		{
			use[v] = true;
			if(ym[v]==-1||dfs(ym[v]))
			{
				ym[v] = u;			//能找到一条增广路的话，取反操作
				return true;
			}
		}
		return false;
}
int hungry()			//匈牙利算法
{
	memset(ym,-1,sizeof(ym));
	int ret = 0;
	for(int u=1;u<=n;u++)	//从顶点u出发找一条增广路
	{
		memset(use,false,sizeof(use));
		if(dfs(u))			//能找到的话，匹配数加一
			ret++;
	}
	return ret;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t,u,v;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		memset(g,false,sizeof(g));
		while(m--)
		{
			scanf("%d%d",&u,&v);
			g[u][v] = true;			//从u出发，到v结束
		}
		printf("%d\n",n-hungry());
	}
	return 0;
}