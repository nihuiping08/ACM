/*

���⣺ֵ�����⣬ÿ���˶��п��е�ʱ��Σ�ֻ������Щʱ����ڽ��а��ţ��Ƿ��ܰ��źá�

���룺����ÿ���˵Ŀ���ʱ��Ρ�

������Ƿ��ܰ��ųɹ���

˼·����ͼ��������Hungary�㷨��

*/
/*

��Ŀ��
	ֵ�����⣬���������˵Ŀ���ʱ�䣬���ܲ��ܹ���ÿһ��ʱ���ﰲ��һ����ֵ��

������
	����ƥ�����⣬���������Ŀ���ʱ�����߹�ͼ��Ȼ�����hungry�㷨�ˣ���

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
				g[i][x] = true;//���������Ŀ���ʱ����ͨ
			}
		}
		if(hungry()==k)			//����ܹ����źõĻ�
			printf("yes\n");
		else
			printf("no\n");
		//printf("%d\n",hungry());
	}
	return 0;
}