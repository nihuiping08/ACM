/*
题目：
	若某个家族人员过于庞大，要判断两个是否是亲戚，确实还很不容易，
	现在给出某个亲戚关系图，求任意给出的两个人是否具有亲戚关系。
 
	规定：x和y是亲戚，y和z是亲戚，那么x和z也是亲戚。如果x,y是亲戚，
	那么x的亲戚都是y的亲戚，y的亲戚也都是x的亲戚。
	Input
	多组case，每组case中，第一行输入N(1 ≤ N ≤ 5000),M(1 ≤ M ≤ 5000),
	Q(1 ≤ Q ≤ 5000)，分别表示人数，关系数，询问次数。
	接着输入M行，每行两个整数a,b，表示a和b之间有亲戚关系。
	接着输入Q行，每行两个整数a,b，表示询问a和b之间是否有亲戚关系。
	注：人的下标从1开始。
	Output
	为每条询问输入一行，当有亲戚关系时，输出yes，否则输出no.
	Sample Input
	5 2 3
	1 2
	2 3
	1 3
	2 4
	3 5 
	Sample Output
	yes
	no
	no

分析：
	考察并查集，注意到数据比较大，所以输入输出都得用scanf()和printf()函数，
	不然就会time limitted，并且需要优化了的并查集查询，可以用路径压缩的方法，
	即我们找到最久远的祖先时“顺便”把它的子孙直接连接到它上面。这就是路径压缩了。
	使用路径压缩的代码如下，时间复杂度基本可以认为是常数的。时间复杂度O(n*α(n))
	其中α(x)，对于x=宇宙中原子数之和，α(x)不大于4事实上，路经压缩后的并查集的复
	杂度是一个很小的常数。

	合并操作：
	C语言代码： 合并时将元素所在深度低的集合合并到元素所在深度深的集合。
	void union_set(int x ,int y)
	{
	     fx = find_set(x);
	     fy = find_set(y);
	 
	     if (Rank[fx]>Rank[fy])
	        father[fy] = fx;
	     else
	     {
	        father[fx] = fy;
	        if(Rank[fx]==Rank[fy])
	           Rank[fx]++;
	     }
	}
	///////////初始化
	void init(void)
	{
	    int i;
	    for (i=0; i<MAX; i++)
	        father[i] = i;
		memset(Rank,0,sizeof(Rank));
	}
	//////寻找最早的祖先
	int find_set(int v)
	{
	    if (father[v] != v)
	        father[v] = find_set(father[v]);
	    return father[v];
	}
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 5010
int p[X],set[X];
int Rank[X];
int find_set(int x)
{	//查找最早的祖先
	if(x!=set[x])
		set[x] = find_set(set[x]);
	return set[x];
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,m,q,a,b;
	while(cin>>n>>m>>q)
	{
		for(int i=0;i<=n;i++)
			set[i] = i;
		memset(Rank,0,sizeof(Rank));
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&a,&b);
			///////////压缩路径
			int fx = find_set(a);
			int fy = find_set(b);
			if(Rank[fx]>Rank[fy])
				set[fy] = fx;
			else
			{
				set[fx] = fy;
				if(Rank[fx]==Rank[fy])
					Rank[fy]++;
			}
		}
		for(int i=1;i<=q;i++)
		{
			scanf("%d%d",&a,&b);
			int x = find_set(a);
			int y = find_set(b);
			if(x!=y)
				printf("no\n");
			else
				printf("yes\n");
		}
	}
	return 0;
}


