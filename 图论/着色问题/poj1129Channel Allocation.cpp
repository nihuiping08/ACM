#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
#define X 305
string s;
int map[X][X],color[X],n,x,y,len,c,ans;
bool check(int a,int col)	//检查顶点a的颜色能否涂成col
{
	for(int i=1;i<=n;i++)
		if(map[a][i]&&color[i]==col)	//相邻节点颜色与他一样，不行
			return false;
	return true;
}
bool dfs(int tc,int v)	//搜索颜色总数为tc时，正在要涂色的是顶点v
{
	if(tc==n)	//如果颜色总数等于n，因为之前的用较少的颜色都不能涂好，所以此处可直接返回真
		return true;
	if(v==n+1)	//如果把n个节点都涂完的话，直接返回真
		return true;
	for(int i=1;i<=tc;i++)	//从颜色1开始枚举，看看当前颜色是否能涂满所有顶点
	{
		color[v] = i;
		if(check(v,i))	//判断是否可以涂成颜色i
			if(dfs(tc,v+1))	//如果下面的顶点同样能涂好，返回真
				return true;
	}
	return false;
}
int solve()	//根据平面图的4色定理，枚举颜色1到4即可
{
	//////直接用1种颜色看看是否能涂好
	bool flag = true;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(map[i][j])
				flag = false;
	if(flag)
		return 1;

	for(int i=2;i<=4;i++)	//从2开始枚举
	{
		memset(color,0,sizeof(color));
		if(dfs(i,1))
			return i;
	}
	return -1;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	while(cin>>n,n)
	{
		ans = 1;
		memset(map,0,sizeof(map));
		for(int i=0;i<n;i++)
		{
			cin>>s;
			len = s.size();
			x = s[0] - 'A'+1;	//转化为图的邻接矩阵表示形式，切下标从1开始
			for(int j=2;j<len;j++)
			{
				c = s[j]-'A'+1;
				map[x][c] = map[c][x] = 1;
			}
		}
		int ans = solve();
		if(ans==1)
			printf("1 channel needed.\n");
		else
			printf("%d channels needed.\n",ans);
	}
	return 0;
}