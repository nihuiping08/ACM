/*
题目：
	给出两个顶点并且给出两个顶点之间的概率，求从1到n的最大的概率
分析：
	纯粹是dijkstra算法，只不过把最短路径改动一下而已
	要先定义dp[n]=1;后面的直接套用dijkstra模板，把min部分改为max即可，
	并且之前加的部分改为相乘即可

dijkstra模板：
	设图由邻接矩阵g存储。	memset(dist,0x3f,sizeof(dist));	memset(used,false,sizeof(used));	dist[0]=0;//设0为源点	for(i=0;i<n;i++)//循环n次	{		min=10000000;		for(j=0;j<n;j++)//找到最小值			if(!used[j]&&dist[j]<min)			{				min=dist[j];				k=j;			}		used[k]=true;		for(j=0;j<n;j++)//更新其它点			dist[j]=min(dist[j],dist[k]+g[k][j]);	}
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
		{	//把对应的两顶点之间的概率付给对应的顶点，
			cin>>a>>b>>p;
			map[a][b] = p/100;	//因为是无向图，两边都得赋值
			map[b][a] = p/100;
		}
		double sum = 1;
		dp[1] = 1;
		int k;
		for(int i=1;i<=n;i++)
		{	//dijkstra模板
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