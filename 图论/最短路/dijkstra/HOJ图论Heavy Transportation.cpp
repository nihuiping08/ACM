/*
��Ŀ:
	���Ǹ��˿����������еĳ��е����������Ƕ���
������
	������������ıߵ���Сֵ��������dijkstra�㷨���������൱�ڰ�����Сֵ��Ϊ�����ֵ��
	ֻ���dist��ʼ��Ϊ0������min����Ϊmax = -1,ע�⵽����Ϊ0���ٸĶ������ط����У�
	��ϸ�����롣����

	��ͼ���ڽӾ���g�洢��
	memset(dist,0x3f,sizeof(dist));
	memset(used,false,sizeof(used));
	dist[0]=0;//��0ΪԴ��
	for(i=0;i<n;i++)//ѭ��n��
	{
		min=10000000;
		for(j=0;j<n;j++)//�ҵ���Сֵ
			if(!used[j]&&dist[j]<min)
			{
				min=dist[j];
				k=j;
			}
		used[k]=true;
		for(j=0;j<n;j++)//����������
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
		memset(map,0,sizeof(map));//��ʼ��Ϊ0����Ϊ���������������е���Сֵ
		memset(dis,0,sizeof(dis));
		cin>>n>>m;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			map[x][y] = map[y][x] = z;
		}
		memset(use,false,sizeof(use));//���δ��ʹ��
		int k,MAX;
		dis[1] = 100000000;//ע��˴��ñ��Ϊ����10000000
		/////dijkstraģ��Ķ�һ��
		for(int i=1;i<=n;i++)
		{
			MAX = -1;	//�˴���Ϊ���ֵ
			for(int j=1;j<=n;j++)
				if(!use[j]&&MAX<dis[j])//��ΪС�ں�
					 MAX = dis[k=j];
			use[k] = true;
			for(int j=1;j<=n;j++)
				if(!use[j]&&dis[j]<min(dis[k],map[k][j]))//����
					dis[j] = min(dis[k],map[k][j]);
		}
		printf("Scenario #%d:\n",cnt++);
		cout<<dis[n]<<endl;
		if(t)
			cout<<endl;
	}
	return 0;
}


