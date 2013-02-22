/*

��Ŀ��
	�����·�ʹζ�·�ǲ���һ������

������
	������prim�����С������������ö��ÿ������������С�������бߣ���һ��
	������С�������еıߣ�����ͨ��ȥ�滻��С�������е�һ���ߣ�Ȼ���ж��ǲ�����
	֮ǰ�������Сֵ���

*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define X 105
#define INF 10000000
int map[X][X],path[X][X],dis[X],pre[X],n,m;
bool use[X],visit[X][X];
int prim()
{
	memset(use,false,sizeof(use));		//��prim�м�¼�Ƿ��ù�
	memset(visit,false,sizeof(visit));	//��ʾ���Ƿ��������С��������
	memset(pre,0,sizeof(pre));			//ǰ������
	memset(path,0,sizeof(path));		//��¼��С����������������֮�����ߵ�ֵ

	for(int i=2;i<=n;i++)
		dis[i] = INF;
	dis[1] = 0;
	int MIN,k,ans = 0;

	for(int i=0;i<n;i++)
	{
		MIN = INF;
		for(int j=1;j<=n;j++)
			if(!use[j]&&dis[j]<MIN)
				MIN = dis[k=j];

		if(MIN==INF)
			return INF;

		////////////////////////////////////////////��Ĳ���
		int p = pre[k];
		path[p][k] = MIN;
		visit[p][k] = visit[k][p] = true;//��������С�������У����Ϊtrue  

		for(int j=1;j<=n;j++)
			if(use[j])	//��������������С�������еĵ㵽u��max_val[i][u]  
				//path[j][k] = path[j][p]>path[p][k]?path[j][p]:path[p][k];
				path[j][k] = max(path[j][p],path[p][k]);
				//����ǰ���϶��Ѿ������£�����ֻ��Ҫj��p��p��k�Ƚϼ���
		//////////////////////////////////////////

		use[k] = true;
		ans += MIN;
		for(int j=1;j<=n;j++)
			if(!use[j]&&map[k][j]<dis[j])
				dis[j] = map[k][j],pre[j] = k;//���k�ܰ�dis[j]���£���k��j��pre  
	}
	return ans;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t,x,y,z;
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				map[i][j] = INF;
		while(m--)
		{
			scanf("%d%d%d",&x,&y,&z);
			map[x][y] = map[y][x] = z;
		}
		int ans = prim();	//�������С������
		bool flag = true;
		for(int i=1;i<=n&&flag;i++)
			for(int j=1;j<=n&&flag;j++)
				if(!visit[i][j]&&map[i][j]!=INF)//��һ��������С�������еıߣ�����ͨ��ȥ�滻��С�������е�һ����  
					if((ans+map[i][j]-path[i][j])==ans)
						flag = false;
		if(flag)
			cout<<ans<<endl;
		else
			cout<<"Not Unique!"<<endl;
	}
	return 0;
}