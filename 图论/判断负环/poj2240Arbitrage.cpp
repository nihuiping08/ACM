/*
题目：
	问周游一圈后能不能换钱得到利润
分析：
	有向图是否处在负环问题，因为涉及每个顶点都可能存在负环，
	直接用flord算法做即可
*/
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
#define X 35
string city[X],s1,s2;
double map[X][X];
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int m,n,x,y,cnt = 0;
	double dis;
	while(cin>>n,n)
	{
		memset(map,0,sizeof(map));
		for(int i=0;i<n;i++)
		{
			cin>>city[i];
			map[i][i] = 1;
		}
		cin>>m;
		for(int i=0;i<m;i++)
		{
			cin>>s1>>dis>>s2;
			for(int j=0;j<n;j++)//找出起点终点
			{
				if(s1==city[j])
					x = j;
				if(s2==city[j])
					y = j;
			}
			map[x][y] = dis;	//有向图的路径长度
		}
		for(int k=0;k<n;k++)	//fload算法
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					if(map[i][j]<map[i][k]*map[k][j])		//松弛操作
						map[i][j] = map[i][k]*map[k][j];
		bool flag = true;
		for(int i=0;i<n;i++)
			if(map[i][i]>1)	//如果存在负环
				flag = false;
		if(!flag)
			printf("Case %d: Yes\n",++cnt);
		else
			printf("Case %d: No\n",++cnt);
	}
	return 0;
}