/*

tarjan算法求割点，上一篇已经解析过了，本篇略过

*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 1002
int dfn[X],ans[X],low[X],map[X][X],n,m,depth;
void init()
{
	memset(map,0,sizeof(map));
	memset(ans,0,sizeof(ans));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	depth = 0;
	n = 0;
}
void dfs(int v)
{
	dfn[v] = low[v] = ++depth;
	for(int i=1;i<=n;i++)
		if(map[v][i]==1)
		{
			map[i][v] = map[v][i] = 2;
			if(!dfn[i])
			{
				dfs(i);
				low[v] = min(low[v],low[i]);
				if(low[i]>=dfn[v])
					ans[v]++;
			}
			else
				low[v] = min(low[v],dfn[i]);
		}
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int x,y,cnt = 0;
	while(cin>>x,x)
	{
		if(cnt)
			cout<<endl;
		init();
		cin>>y;
		n = max(x,y);
		map[x][y] = map[y][x] =  1;
		while(cin>>x,x)
		{
			cin>>y;
			map[x][y] = map[y][x] =  1;
			n = max(n,max(x,y));
		}
		dfs(1);
		ans[1]--;
		bool flag = false;
		printf("Network #%d\n",++cnt);
		for(int i=1;i<=n;i++)
			if(ans[i]>0)
			{
				printf("  SPF node %d leaves %d subnets\n",i,ans[i]+1);
				flag = true;
			}
			if(!flag)
				printf("  No SPF nodes\n");
	}
	return 0;
}