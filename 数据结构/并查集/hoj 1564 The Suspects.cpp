/*
��Ŀ��
	��˵ѧ��0������SARS���������Ӵ����ľ��ֲ����������Լ����Ӵ�������������˽Ӵ���
	���п�����SARS����Ҫ��������������о��ֲ��˵�������Ҫ��������е����ɷ�������
������
	�ò��鼯�ķ�����������ʵ�����ȶ���n��ɭ�֣�Ȼ���ٰ�ͬһ�������ڵ�ɭ�ֺϲ���һ��
	�����鼯�ĸ��Ʒ��������֣��ҵ�ʹ�õ���ѹ��·���ķ���
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int X = 30010;
int parent[X],a[X],Rank[X],m,n,t;
int find_set(int x)					//·��ѹ��
{
	if(x!=parent[x])
		parent[x] = find_set(parent[x]);
	return parent[x];
}
void union_set(int i,int j)
{
	i = find_set(i);
	j = find_set(j);
	if(i!=j)
		if(Rank[i]>Rank[j])			//�ȼ�Խ�ߣ����ڵ����ĸ߶�Խ��
			parent[j] = i;
		else
		{
			parent[i] = j;
			if(Rank[i]==Rank[j])
				Rank[j]++;
		}
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int x,pre;
	while(cin>>n>>m,n||m)
	{
		for(int i=0;i<n;i++)
		{
			parent[i] = i;
			Rank[i] = 0;
		}
		for(int i=0;i<m;i++)
		{
			scanf("%d",&t);
			if(t)					//ֻ���ҳ����ֲ��ĵ�һ�����������˲���������
				scanf("%d",&pre);
			for(int i=0;i<t-1;i++)
			{
				scanf("%d",&x);
				union_set(pre,x);
			}
		}
		pre = find_set(0);		//�ҵ�0���ڵ����ĸ��ڵ��ţ�������������������Ƚ�
		int ans = 1;
		for(int i=1;i<n;i++)
			if(pre==find_set(i))
				ans++;
		cout<<ans<<endl;
	}

	return 0;
}