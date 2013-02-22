/*

题意：题意还是比较简单，有很多job，可以在machine A或者machine B的某种mode只是在二分图匹配的
时候不用考虑第一个机器，它的初始状态可以根据需要进行调整，就是别判断它就行了。

输入：输入比较浪费资源，k个关联关系，就不用每行还输入行号了吧？

输出：最大匹配数。

思路：赤裸裸Hungary算法。首先machine A的mode和machine B的mode构成了一个二分图，二者内部之间
不能有边，如果某个任务可以在machine A的mode x或者machine B的mode y完成，那么从x到y有一条边，
即(x,y) = true，然后求出最大匹配即可。


*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 102
int xm[X],ym[X],n,m;
bool map[X][X],use[X];
int dfs(int u)
{
	for(int i=0;i<m;i++)
		if(map[u][i]&&!use[i])
		{
			use[i] = true;
			if(ym[i]==-1||dfs(ym[i]))
			{
				xm[u] = i;
				ym[i] = u;
				return true;
			}
		}
		return false;
}
int hungry()
{
	int ret = 0;
	memset(xm,-1,sizeof(xm));
	memset(ym,-1,sizeof(ym));
	for(int i=0;i<n;i++)
		if(xm[i]==-1)
		{
			memset(use,false,sizeof(use));
			if(dfs(i))
				ret++;
		}
		return ret;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int k,x,y,z;
	while(cin>>n,n)
	{
		cin>>m>>k;
		memset(map,false,sizeof(map));
		for(int i=0;i<k;i++)
		{
			scanf("%d%d%d",&z,&x,&y);
			if(x&&y)
				map[x][y] = true;
		}
		printf("%d\n",hungry());
	}

	return 0;
}