/*
poj2524
���⣺
	һ��ѧУ��n��ѧ�����в�ͬ���ڽ�����������m������ͬ������ͬѧ�ԣ����n��ͬѧ
	����ж����ֲ�ͬ���ڽ�������

������
	���鼯������
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 50005
int Rank[X],father[X],a[X];
int find_set(int x)					//���Ҹ��ڵ�
{
	if(x!=father[x])
		father[x] = find_set(father[x]);
	return father[x];
}
void union_set(int x,int y)
{
	x = find_set(x);
	y = find_set(y);
	if(x!=y)
		if(Rank[x]>Rank[y])
			father[y] = x;
		else
		{
			father[x] = y;
			if(Rank[x]==Rank[y])
				Rank[y]++;
		}
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int m,n,x,y,cnt = 0;
	while(cin>>n>>m,n||m)
	{
		for(int i=0;i<=n;i++)
		{
			Rank[i] = 0;
			father[i] = i;
			a[i] = 0;
		}
		for(int i=0;i<m;i++)
		{
			scanf("%d%d",&x,&y);
			union_set(x,y);
		}
		int q,ans = 0;
		for(int i=1;i<=n;i++)
		{
			q = find_set(i);
			if(!a[q])
			{
				ans++;
				a[q] = 1;
			}
		}
		printf("Case %d: %d\n",++cnt,ans);
	}
	return 0;
}