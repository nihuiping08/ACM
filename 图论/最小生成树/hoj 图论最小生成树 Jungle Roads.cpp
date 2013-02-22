/*
题目：
	岛上的居民要修最短的路来使得费用最少
分析：
	实际上是求最小生成树，可以用prim算法和kruskal算法，
	基于刚学kruskal算法，以下是用kruskal算法做的。

	kruskal算法的思想是:
	先把所有的边按照非降序排列，从而观察每条边是否能与以前
	的边组成环，能的话就不选，不能的话就选择，而判断是否组
	成环路的话可以通过使用并查集实现

	并查集的思想是：
	{1,2,3},{4,5},{6,7,8},{9},当该边是当前最少的边时，两端顶点为
	1,4，因为1,4在两个不同的集合中，故而不能组成回路，假设在同一
	集合中，如1和2，因为前面肯定1,2,3能直接或间接相连接，加入边(1,2)
	可定能使该图组成环路，故而可以用以下代码实现并查集：假设边(u,v)
	的边定点为u[i],v[i],长度为len[i]
	int find_set(int x)
	{
		if(x==union_set[x])
			return x;
		return find_set(union_set[x]);
	}
	以下是main函数里即可实现
	int ans = 0;
	for(int i=0;i<=cnt;i++)
		union_set[i]=i;
	int x = find_set(u[i]);
	int y = find_set(v[i]);
	if(x!=y)
	{
		union_set[y]=x;
		ans+=len[i];
	}
	答案即为ans
*/
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
#define X 150
int union_set[80];//并查集
typedef struct node
{	//定义结构体
	int u,v,len;//顶点，顶点，长度
}node;
struct node p[X];
int find_set(int x)
{	//查找该元素所在集合
	if(x==union_set[x])
		return x;
	return find_set(union_set[x]);
}
int cmp(const void *a,const void *b)
{	//强转为结构体排序，按长度的非降排序
	struct node *c = (struct node *)a;
	struct node *d = (struct node *)b;
	return c->len-d->len;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n;
	while(cin>>n,n)
	{
		int a,b;
		char ch1,ch2;
		int cnt = 0;
		for(int i=0;i<n-1;i++)
		{
			cin>>ch1>>a;
			for(int j=0;j<a;j++)
			{
				cin>>ch2>>b;
				p[cnt].u = ch1-'A';
				p[cnt].v = ch2-'A';
				p[cnt].len = b;
				cnt++;
			}
		}
		qsort(p,cnt,sizeof(p[0]),cmp);//排序
		
		//刚开始的时候是n个森林，每一个元素均为该集合的序号
		for(int i=0;i<=cnt;i++)
			union_set[i] = i;
		int ans = 0;
		for(int i=0;i<cnt;i++)
		{
			int x = find_set(p[i].u);//查找顶点所在集合序号
			int y = find_set(p[i].v);
			if(x!=y)
			{
				union_set[y] = x;
				ans += p[i].len;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}