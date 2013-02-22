/*

题意：现在John要去访问他的朋友,在这个城市中有n条街道,每条街道与别的街道有两个交点,现在
给出这些街道的信息(即输入x y z表示街道z的两个端点为x,y),问其是否可以每条街道只经过一次,
如果存在,则输出字典序最小的路线,不存在则输出"Round trip does not exist."。街道数 < 1995，
一个城市最多连接44条道路。路径用栈来保存，输出时从栈顶开始输出，能保证字典序最小。这是因为
dfs的时候路径编号是渐增的，编号小的路径自然先被遍历。

算法：dfs

注意：建图的时候记录的是点和边的关系


题意：有个人想访问所有的好友，不走重复的路，街道有编号，如果访问好友有很多种选择的话，
选择编号最小的走，判断是否存在这样的路，如果存在输出路径标号。

输入：街道和交叉口的编号，起点是第一条街道中的较小点。

输出：如果有路输出路径编号，如果没有输出信息。

思路：这道题目首先题目告诉是个连通图，所以不用判断是否连通，然后判断欧拉回路。之后就是
DFS走一遍这条路，保存在栈中，然后倒序打印即可。


*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <stack>
using namespace std;
#define X 2000
int map[45][X],in[X],n,m,start;
bool visit[X];
stack<int> s;
bool is_euler()			//所有的顶点都要为偶数度
{
	for(int i=1;i<=n;i++)
		if(in[i]%2)
			return false;
	return true;
}
void init()
{
	m = n = 0;
	memset(map,0,sizeof(map));
	memset(in,0,sizeof(in));
	memset(visit,false,sizeof(visit));
}
void add(int x,int y,int z)
{
	m++;
	n = max(n,z);
	map[x][z] = y;
	map[y][z] = x;
	in[x]++;
	in[y]++;
}
void dfs(int x)
{
	for(int i=1;i<=n;i++)
		if(map[x][i]&&!visit[i])
		{
			visit[i] = true;
			dfs(map[x][i]);
			s.push(i);
		}
}
void print()
{
	if(is_euler())
	{
		dfs(start);
		bool flag = false;
		while(s.size())
		{
			if(flag)
				printf(" ");
			printf("%d",s.top());
			flag = true;
			s.pop();
		}
	}
	else
		printf("Round trip does not exist.");
	printf("\n");
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int x,y,z;
	while(scanf("%d%d",&x,&y),x||y)
	{
		init();
		scanf("%d",&z);
		start = min(x,y);
		add(x,y,z);
		while(scanf("%d%d",&x,&y),x||y)
		{
			scanf("%d",&z);
			add(x,y,z);
		}
		print();
	}

	return 0;
}