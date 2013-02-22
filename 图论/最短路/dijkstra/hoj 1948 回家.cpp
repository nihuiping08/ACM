/*

��Ŀ��
	�ؼҵ�ÿ�ξ����ĳ��������֣����𳵵��������������������������֮���ת��ʱ�䲻ͬ��
	�����ٻؼ�ʱ�䡣

������
	������Ŀ���ݽ�С��ֱ����STL�е�map����¼���еı��,ע�⵽map<string,int> mp
	�ĳ�ֵΪ0�����Եô�1��ʼ��������ת�𳵻��߻�ת����������dijkstra�Ļ���������һ��
	������map[X][X][2],dis[X][2]��2������¼�������𳵻�������������Ϣ����dijkstra�㷨
	�ϼ���һ��for���ѯ�ʲ�ͬ��ʽ����Сʱ�䡣���忴����

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
				if(!use[j][k]&&dis[j][k]<MIN)	//����һ��ѭ���Լ�һ����¼��
					MIN = dis[p=j][q=k];
		use[p][q] = true;
		for(int j=1;j<=n;j++)
			for(int k=0;k<2;k++)
				if(!use[j][k])		//�ɳڲ���������ʽһ��ʱΪ3������Ϊ10
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
					ma[i][j][k] = INF;//��ʼ����ͼ
		while(t--)
		{
			cin>>form>>start>>pass>>di;
			if(!mp[start])		//����map�в����ڵĻ���map���ص���0
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