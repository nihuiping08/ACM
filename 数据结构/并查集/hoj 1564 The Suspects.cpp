/*
题目：
	是说学生0怀疑有SARS病，跟他接触过的俱乐部的所有人以及他接触过的人再与别人接触，
	都有可能有SARS病，要你求出给出的所有俱乐部人的名单，要你求出所有的嫌疑犯。。。
分析：
	用并查集的方法做，具体实现是先定义n个森林，然后再把同一的人所在的森林合并在一起，
	而并查集的改善方法有两种，我的使用的是压缩路径的方法
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int X = 30010;
int parent[X],a[X],Rank[X],m,n,t;
int find_set(int x)					//路径压缩
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
		if(Rank[i]>Rank[j])			//等级越高，所在的树的高度越高
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
			if(t)					//只需找出俱乐部的第一个人与其他人并起来即可
				scanf("%d",&pre);
			for(int i=0;i<t-1;i++)
			{
				scanf("%d",&x);
				union_set(pre,x);
			}
		}
		pre = find_set(0);		//找到0所在的树的根节点编号，再用它与其他的人相比较
		int ans = 1;
		for(int i=1;i<n;i++)
			if(pre==find_set(i))
				ans++;
		cout<<ans<<endl;
	}

	return 0;
}