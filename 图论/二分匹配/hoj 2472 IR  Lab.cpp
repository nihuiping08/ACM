/*

题意：值班问题，每个人都有可行的时间段，只能在这些时间段内进行安排，是否能安排好。

输入：给出每个人的可行时间段。

输出：是否能安排成功。

思路：建图，赤裸裸Hungary算法。

*/
/*

题目：
	值班问题，给出所有人的空余时间，问能不能够在每一个时间里安排一个人值班

分析：
	二分匹配问题，按人与他的空余时间连线构图，然后就是hungry算法了，简单

*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 22
bool g[X][X],use[X];
int xm[X],ym[X],k,p;
bool dfs(int u)
{
	for(int v=0;v<k;v++)
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
	int ret = 0;
	memset(xm,-1,sizeof(xm));
	memset(ym,-1,sizeof(ym));
	for(int u=0;u<p;u++)
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
	while(cin>>k>>p,k||p)
	{
		int t,x;
		memset(g,false,sizeof(g));
		for(int i=0;i<p;i++)
		{
			scanf("%d",&t);
			while(t--)
			{
				scanf("%d",&x);
				g[i][x] = true;//该人与他的空余时间连通
			}
		}
		if(hungry()==k)			//如果能够安排好的话
			printf("yes\n");
		else
			printf("no\n");
		//printf("%d\n",hungry());
	}
	return 0;
}