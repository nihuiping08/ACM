/*

题目：
	象棋中的车在象棋盘上可以放置的最大数目（若没有挡板的话，在同一行或同一列的车
	可以相互攻击，问的是所有的车可以和平地放置的最大数目）

分析：
	方法一：
		可以通过暴搜得到答案（题目数据较小）
	方法二：
		可以通过构造二分图的方法来做，以下主要分析二分图的解法

方法：
	我们将每一行，每一列被墙隔开，且包含空地的连续区域称作“块”。显然，在一个块之中，
	最多只能放一个车。我们把这些块编上号。
	同样，把竖直方向的块也编上号。
	把每个横向块看作X部的点，竖向块看作Y部的点，若两个块有公共的空地，则在它们之间连边。
	于是，问题转化成这样的一个二部图：

	.X..
	....
	XX..
	....

	我们可以给上面的图形标号（X部）:r[i][j]	1  -1   2   2	3   3   3   3	-1 -1   4   4	5   5   5   5

	接着对Y部进行标号（Y部）：c[i][j]
	1  -1  5  6
	1   3  5  6
	-1 -1  5  6
	2   4  5  6
	若该位置上不为隔板，则只需对g[r[i][j]][c[i][j]] = true即可构建
	一个二分图，剩下的就是赤裸裸的hungry算法了。

	现在转为对数组c和数组r的计算问题，其实我们可以枚举每一个位置上是否为
	空地，若为空地则r[i][j] = n(n为当前的最大标号)，每当遇到隔板时，设旗帜
	为真，每当遇到新的空地时，先对n加一，在赋值给r[i][j]，列的同理计算。
	另外需注意如此做法的数组g（标记有没有连线）的最大下标会发生变化，即最大值
	会大于4而不会大于16（4*4）

*/
//#include <iostream>	//发现每次去掉这两句时，内存都会少400k
#include <cstdio>
#include <cstring>
//using namespace std;
#define X 20
int ym[X],c[X][X],r[X][X],n,m;
bool g[X][X],use[X];
bool dfs(int u)				//寻找增广轨算法
{
	int t;
	for(int v=1;v<=m;v++)
		if(g[u][v]&&!use[v])
		{
			use[v] = true;
			t = ym[v];
			ym[v] = u;			//通过取反操作尝试能不能找到增广轨
			if(t==-1||dfs(t))	//能够找到的话
				return true;
			ym[v] = t;			//不能找到的话，付回原值
		}
		return false;
}
int hungry()			//匈牙利算法
{
	int ret = 0;
	memset(ym,-1,sizeof(ym));
	for(int u=1;u<=n;u++)	//从顶点u开始看看能不能找到一条增广路
	{
		memset(use,false,sizeof(use));//能找到的话，匹配加1
		if(dfs(u))
			ret++;
	}
	return ret;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t;
	char ch[X][X];
	while(scanf("%d",&t),t)
	{
		for(int i=0;i<t;i++)
			scanf("%s",ch[i]);
		memset(g,false,sizeof(g));
		n = m = 0;
		bool flag;
		memset(r,0,sizeof(r));
		for(int i=0;i<t;i++)
		{
			flag = true;
			for(int j=0;j<t;j++)		//算行的标号
			{
				if(ch[i][j]=='.')
				{
					if(flag)			//如果为真，表明前面有隔板，说明标号比前面的大1
						n++;
					r[i][j] = n;		//赋值
					flag = false;
				}
				else					//设立旗帜
				{
					flag = true;
					r[i][j] = -1;
				}
			}
			flag = true;
			for(int j=0;j<t;j++)	//寻找列的标号
			{
				if(ch[j][i]=='.')
				{
					if(flag)
						m++;
					flag = false;
					c[j][i] = m;
				}
				else
				{
					flag = true;
					c[j][i] = -1;
				}
			}
		}
		for(int i=0;i<t;i++)
			for(int j=0;j<t;j++)
				if(c[i][j]!=-1&&r[i][j]!=-1)
					g[r[i][j]][c[i][j]] = true;//构造连线
		printf("%d\n",hungry());
	}
	return 0;
}