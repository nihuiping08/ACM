/*

题目：
	当一个洋娃娃的长宽高都比另一个大时，小的那个可以被套进去，问在最外面的洋娃娃的
	最小个数

分析：
	求最大独立集，用娃娃总数-最大匹配即可，用两层循环先建图，每当娃娃i长宽高都比j小时，
	则g[i][j] = true建图即可，开始时我竟然先对它进行排序，后来才发现是不用的。。。直接
	两层循环再比较即可建图。求最大匹配就是纯粹的hungy算法

*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 502
int xm[X],ym[X],n,m;
bool g[X][X],use[X];
struct node
{
	int a,b,c;
}p[X];
bool dfs(int u)
{
	for(int v=1;v<=n;v++)
		if(g[u][v]&&!use[v])
		{
			use[v] = true;
			if(ym[v]==-1||dfs(ym[v]))
			{
				xm[u] = v;
				ym[v] = u;
				return true;
			}
		}
		return false;
}
int hungry()
{
	memset(xm,-1,sizeof(xm));
	memset(ym,-1,sizeof(ym));
	int ret = 0;
	for(int u=1;u<=n;u++)
		if(xm[u]==-1)
		{
			memset(use,false,sizeof(use));
			if(dfs(u))
				ret++;
		}
		return ret;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	while(cin>>n,n)
	{
		for(int i=1;i<=n;i++)
			scanf("%d%d%d",&p[i].a,&p[i].b,&p[i].c);
		memset(g,false,sizeof(g));
		for(int i=1;i<=n;i++)	//建图
			for(int j=1;j<=n;j++)
				if(i!=j&&p[j].a>p[i].a&&p[j].b>p[i].b&&p[j].c>p[i].c)//当三者均满足时
					g[j][i] = true;
		printf("%d\n",n-hungry());
	}

	return 0;
}