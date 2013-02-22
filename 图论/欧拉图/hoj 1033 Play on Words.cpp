/*

用了iostream和using namespace std;之后竟然内存差了400多K，看来C++除了耗时间，还
耗内存。

题目：
	题意：字符串连起来组成密码才能开门，必须所有的字符串都用到，连接的字母首尾相接。
	输入：所有的字母。
	输出：是否可以完成连接。

思路：
	把26个字母看做节点，单词看做边，对于每一个单词，首字母的出度加1，尾字母的入读加1，
	二者连通，然后判断这个图是否连通，再判断是否有欧拉路或者欧拉回路即可。

欧拉回路:
	1.所有顶点的入度等于出度(有向图)，或者只有两个顶点的出度不等于入度，且该两个顶点
		必须有一个出度等于入度加一，另一个入度等于出度加一，否则不是欧拉图。
	2.另外，若图不连通的话，也没有欧拉图。判断连不连通，可以通过dfs实现，具体看代码

*/
#include <cstdio>
#include <cstring>
#define X 27
int in[X],out[X],n,cnt;
bool use[X],map[X][X];
char s[1005];
void init()				//初始化
{
	memset(in,0,sizeof(in));
	memset(out,0,sizeof(out));
	memset(use,false,sizeof(use));
	memset(map,false,sizeof(map));
	cnt = 0;
}
void input()		//输入函数
{
	int start,end;
	for(int i=0;i<n;i++)
	{
		scanf("%s",s);
		start = s[0]-'a';
		end = s[strlen(s)-1]-'a';
		in[end]++;		//入度
		out[start]++;	//出度
		use[start] = use[end] = true;
		map[start][end] = map[end][start] = true;
	}
}
void dfs(int start)				//从开始的顶点开始，寻找下一个顶点
{
	use[start] = false;
	cnt--;
	for(int i=0;i<X;i++)
		if(use[i]&&map[start][i])//没有被访问且存在通路
			dfs(i);
}
bool connect()				//判断连不连通
{
	int start;
	for(int i=0;i<X;i++)
		if(use[i])
			cnt++,start = i;//找到所有字母数且任意找一作为起点
	dfs(start);
	if(cnt)
		return false;
	return true;
}
bool is_euler()		//判断入度出度关系
{
	int start = 0,end = 0;
	for(int i=0;i<X;i++)
	{
		if(use[i])
		{
			if(in[i]==out[i])
				continue;
			else if(in[i]==out[i]+1)
				end++;
			else if(in[i]+1==out[i])
				start++;
			else
				return false;
		}
	}
	if(start==end)
		if(!start||start==1)
			return true;
	return false;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		init();
		input();
		if(is_euler()&&connect())
			printf("Ordering is possible.\n");
		else
			printf("The door cannot be opened.\n");
	}
	return 0;
}