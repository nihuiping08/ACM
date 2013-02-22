/*
题目:
	问那个人可以走完所有的城市的最大承载量是多少
分析：
	求最大生成树的边的最小值，可以用dijkstra算法变形做，相当于把求最小值改为求最大值，
	只需把dist初始化为0，并且min处改为max = -1,注意到可能为0，再改动其他地方就行，
	详细看代码。。。

	设图由邻接矩阵g存储。
	memset(dist,0x3f,sizeof(dist));
	memset(used,false,sizeof(used));
	dist[0]=0;//设0为源点
	for(i=0;i<n;i++)//循环n次
	{
		min=10000000;
		for(j=0;j<n;j++)//找到最小值
			if(!used[j]&&dist[j]<min)
			{
				min=dist[j];
				k=j;
			}
		used[k]=true;
		for(j=0;j<n;j++)//更新其它点
			dist[j]=min(dist[j],dist[k]+g[k][j]);
	}
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 1005
long int map[X][X],dis[X];
bool use[X];
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t,m,n,x,y,z;
	int cnt = 1;
	cin>>t;
	while(t--)
	{
		memset(map,0,sizeof(map));//初始化为0，因为求的是最大生成树中的最小值
		memset(dis,0,sizeof(dis));
		cin>>n>>m;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			map[x][y] = map[y][x] = z;
		}
		memset(use,false,sizeof(use));//标记未经使用
		int k,MAX;
		dis[1] = 100000000;//注意此处得标记为大于10000000
		/////dijkstra模板改动一下
		for(int i=1;i<=n;i++)
		{
			MAX = -1;	//此处改为最大值
			for(int j=1;j<=n;j++)
				if(!use[j]&&MAX<dis[j])//改为小于号
					 MAX = dis[k=j];
			use[k] = true;
			for(int j=1;j<=n;j++)
				if(!use[j]&&dis[j]<min(dis[k],map[k][j]))//改了
					dis[j] = min(dis[k],map[k][j]);
		}
		printf("Scenario #%d:\n",cnt++);
		cout<<dis[n]<<endl;
		if(t)
			cout<<endl;
	}
	return 0;
}


