/*

差分约束系统ballman-ford做法

题意：给出n个变量，m个约束公式 asi + asi+1 + .... + asi+ni < ki or >b ki ,叫你判断是否存在着解
	满足这m组约束公式。
 
题解：
	对于 asi + asi+1 + ....... + asi + n < ki or > ki,因为ai和ki都为整，设sum[n] 为 变量ai
	的前n个和，则可以转化为 sum[si+n] - sum[si-1] <= ki -1 or sum[si-1] - sum[si+n] <= -1-ki ,
	这样问题就转化为差分约束的情况。体会了差分约束系统的两个性质。第一就是处理的只能是>=或
	者<=。第二就是差分约束系统的解可以平移。开始做这题的时候就没注意到题中是>和<。

*/

/*
	
	sum[si+ni]-sum[si-1]>w,
	即sum[si-1]-sum[si+ni]<=-w-1
	sum[si+ni]-sum[si-1]<w,
	即sum[si+ni]-sum[si-1]<=w-1

*/
#include <iostream>
#include <cstdio>
using namespace std;
#define X 200
#define INF 0xfffffff
struct node
{
	int u,v,weight;
}p[X*X/2];
int dis[X],m,n;
void add(int i,int u,int v,int w)
{
	p[i].u = u;
	p[i].v = v;
	p[i].weight = w;
}
void bellman_ford()
{
	for(int i=1;i<=n;i++)
		dis[i] = INF;
	dis[1] = 0;
	int x,y;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			x = p[j].u;
			y = p[j].v;
			dis[y] = min(dis[y],dis[x]+p[j].weight);	//对每一条边进行松弛操作
		}
	}
	for(int j=1;j<=m;j++)
	{
		x = p[j].u;
		y = p[j].v;
		if(dis[y]>dis[x]+p[j].weight)			//检查有没有负环存在
		{
			cout<<"successful conspiracy"<<endl;
			return;
		}
	}
	cout<<"lamentable kingdom"<<endl;
	return;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int a,b,w;
	char ch[3];
	while(cin>>n,n)
	{
		cin>>m;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%s%d",&a,&b,ch,&w);
			b += a;
			b++;			//因为sum[si+ni]-sum[si-1]>w,或<w，si从1开始，所以要对两个下标加一
			if(ch[0]=='g')
				add(i,b,a,-w-1);	//sum[si+ni]-sum[si-1]>w 即sum[si-1]-sum[si+ni]<=-w-1
			else
				add(i,a,b,w-1);	//sum[si+ni]-sum[si-1]<w,即sum[si+ni]-sum[si-1]<=w-1
		}
		bellman_ford();
	}
	return 0;
}