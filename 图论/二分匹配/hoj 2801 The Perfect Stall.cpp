/*

��Ŀ��
	ÿͷ��ţϲ���ڲ�ͬ�ĵط����̣�ÿ���ط�ֻ������һͷ��ţ�������Ĳ��̵ĵط�

������
	�ڲ��̵�����ţ֮�佨��ƥ�䣬Ȼ����hungry�㷨����������ţaϲ����q�ز��̣���
	g[a][q] = true����ͼ����

*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define X 202
int xm[X],ym[X],n,m;
bool g[X][X],use[X];
int dfs(int u)
{
	for(int v=1;v<=m;v++)
		if(g[u][v]&&!use[v])
		{
			use[v] = true;
			if(ym[v]==-1||dfs(ym[v]))
			{
				ym[v] = u;
				xm[u] = v;
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
	while(cin>>n>>m)
	{
		int t,x;
		memset(g,false,sizeof(g));
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&t);
			while(t--)
			{
				scanf("%d",&x);
				g[i][x] = true;
			}
		}
		printf("%d\n",hungry());
	}
	return 0;
}