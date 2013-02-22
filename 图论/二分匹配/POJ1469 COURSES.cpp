/*

学生和课程构成一个二部图，可选课程作为X部，学生选为Y部，构造一个二分图。
然后判断能否为完美匹配

*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 302
int ym[X],p,n;
bool g[X][X],use[X];
bool dfs(int u)
{
	for(int v=1;v<=n;v++)
		if(g[u][v]&&!use[v])
		{
			use[v] = true;
			if(ym[v]==-1||dfs(ym[v]))
			{
				ym[v] = u;
				return true;
			}
		}
		return false;
}
int hungry()
{
	int ret = 0;
	memset(ym,-1,sizeof(ym));
	for(int u=1;u<=p;u++)
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
	int t,m,q;
	scanf("%d",&t);
	while(t--)
	{
		memset(g,false,sizeof(g));
		scanf("%d%d",&p,&n);
		for(int i=1;i<=p;i++)
		{
			scanf("%d",&m);
			while(m--)
			{
				scanf("%d",&q);
				g[i][q] = true;
			}
		}
		hungry()==p?printf("YES\n"):printf("NO\n");
	}
	return 0;
}