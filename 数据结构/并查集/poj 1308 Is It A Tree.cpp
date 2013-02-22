/*
题目：
	问能否组成一棵树
分析：
	注意到该树为有向树，入度不能大于一，同时所有节点都应该能指向根，
	可以用并查集查找是否有共同的根，有的话就不是树了，注意此时应该
	要判断是否有两个入度，就不能用压缩路径的并查集，并且只能把出度
	的点付给入度的点的并查集数组(不知道我自己理解是否有错。。。)，
	最后要判断是不是森林，可以用第一个点来检验与后面所有的节点是否
	有交集，只要有一个没有的话，就是森林而不是树
	（空树也是树。。。）

	从poj中的discuss中找到
	1: 0 0 空树是一棵树
	2: 1 1 0 0 不是树 不能自己指向自己
	3: 1 2 1 2 0 0 不是树....自己开始一直在这么WA  好郁闷 重复都不行呀~~5555
	4: 1 2 2 3 4 5 不是树  森林不算是树(主要是注意自己)
	5: 1 2 2 3 3 4 4 5 5 6 6 7 7 8 8 9 9 1  注意 一个节点在指向自己的父亲或祖先 都是错误的 即 9-->1 错
	6: 1 2 2 1 0 0 也是错误的

*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 1000
//int Rank[X];
int set[X],p[X];
int u[1001],v[1001];
int find_set(int x)	//并查集的查找函数
{
	/*if(x!=set[x])
		set[x] = find_set(set[x]);
	return set[x];*/
	if(x==set[x])
		return x;
	return find_set(set[x]);
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,m,cnt = 1;
	while(cin>>m>>n,m!=-1&&n!=-1)
	{
		if(!m&&!n)
		{	//空树的话，直接输出是树
			printf("Case %d is ",cnt++);
			printf("a tree.\n");
		}
		else
		{
			//memset(Rank,0,sizeof(Rank));
			for(int i=1;i<X;i++)
				set[i] = i;
			int count = 1;
			int flag = 0;
			u[count] = m;
			v[count++] = n;
			while(scanf("%d%d",&m,&n),m||n)
			{
				u[count] = m;
				v[count++] = n;
			}
			for(int i=1;i<count;i++)
			{	//查找是否已有相同的根
				m = find_set(u[i]);
				n = find_set(v[i]);
				if(m==n||n!=v[i])//有相同的根或者入度大于1，不是树
				{
					flag = 1;
					break;
				}
				/*if(Rank[m]>Rank[n])
					set[n] = m;
				else
				{
					set[m] = n;
					if(Rank[m]==Rank[n])
						Rank[n]++;
				}*/
				set[n] = m;
			}
			if(!flag)
			{	//当组成森林时，同样不算是树
				m = find_set(u[1]);
				for(int i=2;i<count;i++)
				{
					n = find_set(v[i]);
					if(m!=n)	//当两个节点没有共同的根，是森林不是树
					{
						flag = 1;
						break;
					}
				}
			}
			printf("Case %d is ",cnt++);
			if(flag)
				printf("not ");
			printf("a tree.\n");
		}
	}
	return 0;
}