/*

题目：
	回家的每次经过的城市有两种：坐火车到达或者坐公共汽车到，而两者之间的转车时间不同，
	问最少回家时间。

分析：
	由于题目数据较小，直接用STL中的map来记录城市的编号,注意到map<string,int> mp
	的初值为0，所以得从1开始，而汽车转火车或者火车转汽车可以在dijkstra的基础上增加一个
	量，即map[X][X][2],dis[X][2]，2用来记录的是坐火车或者坐汽车的信息，在dijkstra算法
	上加上一个for语句询问不同方式的最小时间。具体看代码

*/
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <cstdio>
using namespace std;
#define X 110
#define INF 100000000
string in[X];
string home;
int ma[X][X][2],dis[X][2],n,h;
bool use[X][2];
map<string,int> mp;
void dijkstra()
{
	memset(use,false,sizeof(use));
	memset(dis,0x3f,sizeof(dis));
	int MIN,p,q;
	for(int i=2;i<=n;i++)
		for(int j=0;j<2;j++)
			dis[i][j] = ma[i][1][j];
	dis[1][0] = dis[1][1] = 0;
	for(int i=0;i<2*n;i++)
	{
		MIN = INF;
		for(int j=1;j<=n;j++)
			for(int k=0;k<2;k++)
				if(!use[j][k]&&dis[j][k]<MIN)	//多了一层循环以及一个记录量
					MIN = dis[p=j][q=k];
		use[p][q] = true;
		for(int j=1;j<=n;j++)
			for(int k=0;k<2;k++)
				if(!use[j][k])		//松弛操作，当方式一样时为3，否则为10
					dis[j][k] = min(dis[j][k],dis[p][q]+ma[p][j][k]+(q==k?3:10));
	}
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t;
	string start,pass,form;
	int di,x,y,z;
	while(cin>>home)
	{
		mp.clear();
		mp[home] = 1;
		n = 1;
		cin>>t;
		for(int i=0;i<X;i++)
			for(int j=0;j<X;j++)
				for(int k=0;k<2;k++)
					ma[i][j][k] = INF;//初始化地图
		while(t--)
		{
			cin>>form>>start>>pass>>di;
			if(!mp[start])		//若在map中不存在的话，map返回的是0
				mp[start] = ++n;
			if(!mp[pass])
				mp[pass] = ++n;
			x = mp[start];
			y = mp[pass];
			if(start=="Harbin")
				h = x;
			if(pass=="Harbin")
				h = y;
			if(form[0]=='t')
				z = 0;
			else
				z = 1;
			ma[x][y][z] = ma[y][x][z] = di;
		}
		dijkstra();
		printf("%d\n",min(dis[h][0],dis[h][1]));
	}

	return 0;
}