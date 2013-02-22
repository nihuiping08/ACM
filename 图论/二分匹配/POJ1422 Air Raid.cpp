/*

��Ŀ��
	�ս���Ҫ�����ڴ�ׯ�ϣ�ɡ���������κ�·����½��Ҳ�������ŵ���ֵ��ķ��������Ե�����һ��·�ڡ�
	����ɡ���߹���·�ھͿ��Կ��ɱ���ռ�졣�����ٵ�ɡ��ռ������������е�·�ڡ�

������
	��P * P ��ͼ����һЩ�ߣ�ʹ����Щ���ܹ��������еĶ��㣬����һ���㶼����һ������������Ϊ
	�������С·���������⣬��С·������ = |P| - ���ƥ������PΪͼ�ϵĶ��㼯������ת��Ϊ��
	����ͼ�����ƥ�䡣������Ϊǡ����һ��������һ�������㣬ǡ�ù���һ��X����Y��

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
				ym[v] = u;			//���ҵ�һ������·�Ļ���ȡ������
				return true;
			}
		}
		return false;
}
int hungry()			//�������㷨
{
	memset(ym,-1,sizeof(ym));
	int ret = 0;
	for(int u=1;u<=n;u++)	//�Ӷ���u������һ������·
	{
		memset(use,false,sizeof(use));
		if(dfs(u))			//���ҵ��Ļ���ƥ������һ
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
			g[u][v] = true;			//��u��������v����
		}
		printf("%d\n",n-hungry());
	}
	return 0;
}