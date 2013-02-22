/*
��Ŀ��
	�����������㲢�Ҹ�����������֮��ĸ��ʣ����1��n�����ĸ���
������
	������dijkstra�㷨��ֻ���������·���Ķ�һ�¶���
	Ҫ�ȶ���dp[n]=1;�����ֱ������dijkstraģ�壬��min���ָ�Ϊmax���ɣ�
	����֮ǰ�ӵĲ��ָ�Ϊ��˼���

dijkstraģ�壺
	��ͼ���ڽӾ���g�洢��	memset(dist,0x3f,sizeof(dist));	memset(used,false,sizeof(used));	dist[0]=0;//��0ΪԴ��	for(i=0;i<n;i++)//ѭ��n��	{		min=10000000;		for(j=0;j<n;j++)//�ҵ���Сֵ			if(!used[j]&&dist[j]<min)			{				min=dist[j];				k=j;			}		used[k]=true;		for(j=0;j<n;j++)//����������			dist[j]=min(dist[j],dist[k]+g[k][j]);	}
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 101
double map[X][X];
double dp[X];
bool use[X];
double Max(double a,double b)
{
	return a>b?a:b;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,m;
	while(cin>>n,n)
	{
		cin>>m;
		int a,b;
		double p;
		memset(map,0,sizeof(map));
		memset(dp,0,sizeof(dp));
		memset(use,false,sizeof(use));
		for(int i=1;i<=m;i++)
		{	//�Ѷ�Ӧ��������֮��ĸ��ʸ�����Ӧ�Ķ��㣬
			cin>>a>>b>>p;
			map[a][b] = p/100;	//��Ϊ������ͼ�����߶��ø�ֵ
			map[b][a] = p/100;
		}
		double sum = 1;
		dp[1] = 1;
		int k;
		for(int i=1;i<=n;i++)
		{	//dijkstraģ��
			double maxx = 0;
			for(int j=1;j<=n;j++)
				if(!use[j]&&maxx<dp[j])
				{
					maxx = dp[j];
					k = j;
				}
				use[k] = true;
				for(int j=1;j<=n;j++)
					dp[j] = Max(dp[j],dp[k]*map[k][j]);
		}
		dp[n]*=100;
		printf("%lf percent\n",dp[n]);
	}
	return 0;
}