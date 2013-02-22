/*

标准求割点的做法(tarjan算法)

定理：
	设v是Gpi（是G的一棵深度优先搜索树）中的某一非根顶点，v是G的割点当且仅当
	v有一个子顶点s，使得不存在从s或s的任何后裔顶点指向v的某个真祖先顶点的反向边。
	如图：
		   1-----2
		    \   /
		     \ /
			  3
			 / \
			/   \
		   4-----5
	3为割点，因为以1为根的优先搜索树中，不存在从3或3的任何后裔顶点（即4和5）指向3的
	某个真祖先，同时因为3不是搜索树中的根节点，所以3为割点。
	tarjan算法使用的是dfs来构造一棵深度优先搜索树的，它从顶点1开始，用dfn[v]记录的是
	到达顶点v所用的时间（时间戳），而low[v]记录的是顶点v可以直接到达（即不经过任何的
	其它路径）的最早的祖先，我们用数据来描述一下tarjan算法是如何实现的吧：

	0、用数组map处理各顶点之间的关系:(0表示没直接通路，1表示有直接通路，2表示已经被访问过)
		map[1][2] = map[2][1] = map[1][3] = map[3][1] = map[2][3] = map[3][2] = map[3][4]
		= map[4][3] = map[4][5] = map[5][4] = map[3][5] = map[5][3] = 1

	1、从顶点1出发，记录dfn[1] = low[1] = 1,然后从顶点1开始判断是否有直接通路，所以先搜到
	  的是顶点2，map[1][2] = map[2][1] = 2,由于顶点2还没被访问过（dfn[2]==0），从2出发dfs
	  找到以它为跟的子树
	
	2、dfn[2] = low[2] = 2,由于顶点1与2已经被访问过，搜到3有直接通路，map[2][3] = map[3][2] = 2,
		因为3还没有被访问，dfs访问3

	3、dfn[3] = low[3] = 3,由1开始搜，因为map[1][3] = 1,表示该边还没被访问过，map[1][3] = 
		map[3][1] = 2,由于1已经被访问过，所以顶点3所能到达的最早的真祖先的时间戳为1,即语句：
		low[v] = min(low[v],dfn[i]);的含义。又开始往下搜索，2时map[3][2] = 2已被访问过，所以搜到
		了顶点4，dfs访问4

	4、dfn[4] = low[4] = 4,由1开始到2没有直接通路，3时map[4][3] = 2已经被访问过，搜到了5，因5还没
		被访问，dfs访问5

	5、dfn[5] = low[5] = 5,从1到2没有直接通路，搜到3时，由于顶点3已经被访问过（dfn[3]!=0），所以
		更新一下顶点5所能到达的最早祖先的时间戳，所以low[5] = min(dfn[3],low[5]) = 3,由于没有顶点
		可被访问，所以这次dfs算是结束了，回溯到上一个顶点4

	6、回溯到的是语句low[v] = min(low[v],low[i]);，即low[4] = min(low[4],low[5]) = 3，所以顶点4同
		样可到达的最早的时间戳为3，low[4] = 3，由于low[5] = 3 < dfn[4] = 4,所以顶点4不是割点。回溯
		顶点3

	7、回溯到的是语句low[v] = min(low[v],low[i]);，即low[3] = min(low[4],low[3]) = 3，由于3不是根
		结点，而他的所有后裔能回到的最早时间戳为3，即low[3]>=dfn[3],所以3即为割点ans[3] = 1，回溯到2

	8、不详细讲（low[2] = 1,low[2]<dfn[2]）,回溯到1

	9、由于low[1] = dfn[1],所以顶点1会被误认为是割点（至少这个例子是），所以给ans[1] = 1,所以在dfs
		完全结束后需要给ans[1]--，以免算多一个（假设1不是的话）。由此，tarjan算法结束

*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define X 102
int map[X][X],dfn[X],low[X],ans[X],n,m,depth;
void dfs(int v)
{
	dfn[v] = low[v] = ++depth;
	for(int i=1;i<=n;i++)
		if(map[v][i]==1)
		{
			//cout<<"访问"<<v<<"  被访问"<<i<<endl;
			map[v][i] = map[i][v] = 2;
			if(!dfn[i])		//顶点没有被访问过
			{
				//cout<<"dfs"<<i<<endl;
				dfs(i);		//访问
				low[v] = min(low[v],low[i]);
				//printf("low[%d] = %d\n",v,low[v]);
				if(low[i]>=dfn[v])//因为顶点i及其后裔不存在指向顶点v的真祖先的反向边
					ans[v]++;
			}
			else			//该顶点已被访问过，更新该搜索的顶点的最早祖先
			{
				low[v] = min(low[v],dfn[i]);
				//printf("low[%d] = %d\n",v,low[v]);
			}
		}
}
void init()
{
	memset(map,0,sizeof(map));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(ans,0,sizeof(ans));
	depth = 0;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int x,y;
	while(cin>>n,n)
	{
		init();
		while(cin>>x,x)
		{
			while(getchar()!='\n')
			{
				cin>>y;
				map[x][y] = map[y][x] = 1;//表示连通
			}
		}
		dfs(1);
		ans[1]--;
		int cnt = 0;
		for(int i=1;i<=n;i++)
			if(ans[i]>0)
			{
				//cout<<"割点是："<<i<<endl;
				cnt++;
			}
		cout<<cnt<<endl;
	}

	return 0;
}