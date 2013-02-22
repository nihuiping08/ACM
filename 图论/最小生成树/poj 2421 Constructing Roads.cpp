/*
题意：
	有n个村庄，修路，现在已经存在一些路，求最小花费
分析：
	最小生成树，可以用kruskal算法做的，把已经修好的路用并查集联合起来，
	其他的就跟kruskal算法一样了。数组越界问题到现在还没完全去掉，搞到
	run time error了3次，后来用压缩路径做，发现比不用多了14ms，汗。。。
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;
#define X 15000
int set[X];
int Rank[X];
typedef struct node
{	//定义结构体储存边和两顶点
	int u,v,len;
}node;
struct node p[X];
int cmp(const void *a,const void *b)
{	//按非降序排列
	struct node *c = (struct node *)a;
	struct node *d = (struct node *)b;
	return c->len-d->len;
}
int find_set(int x)
{	//并查集查找函数
	/*
	if(x==set[x])有这标记的是没用压缩路径的做法
		return x;
	return find_set(set[x]);
	*/
	if(x!=set[x])
		set[x] = find_set(set[x]);
	return set[x];
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,q,a,b;
	while(cin>>n)
	{
		p[0].len = p[0].u = p[0].v = -1;//因为排序函数是从p[0]开始的
		int cnt = 1;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				p[cnt].u = i;
				p[cnt].v = j;
				scanf("%d",&p[cnt++].len);
			}
		}
		memset(Rank,0,sizeof(Rank));
		qsort(p,cnt,sizeof(p[0]),cmp);
		for(int i=1;i<=cnt;i++)
			set[i] = i;
		cin>>q;
		for(int i=1;i<=q;i++)
		{		//把已有的道路用并查集方式联合起来
			scanf("%d%d",&a,&b);
			int fu = find_set(a);
			int fv = find_set(b);
			/*if(fu!=fv)
				set[fu] = fv;*/
			if(Rank[fu]>Rank[fv])
				set[fv] = fu;
			else
			{
				set[fu] = fv;
				if(Rank[fu]==Rank[fv])
					Rank[fv]++;
			}
		}
		int ans = 0;
		for(int i=1;i<cnt;i++)
		{	//搜索所有的边，看是否已经联合起来
			int fu = find_set(p[i].u);
			int fv = find_set(p[i].v);
			if(fu!=fv)
			{
				ans+=p[i].len;
				//set[fv] = fu;
			}
			if(Rank[fu]>Rank[fv])
				set[fv] = fu;
			else
			{
				set[fu] = fv;
				if(Rank[fu]==Rank[fv])
					Rank[fv]++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}