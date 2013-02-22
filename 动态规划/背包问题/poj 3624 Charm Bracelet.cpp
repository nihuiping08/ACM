/*
题目：
	在重量不超过m的情况下d最大，01背包问题，其状态转移方程为
	dp[i][j] = max{dp[i-1][j],dp[i-1][j-w[i]]+d[i]}
	因为状态转移时i的变化一样，可以压缩dp，直接开一维的数组
	dp[j]=max{dp[j],dp[j-w[j]]+d[j]}，另外，因为j是从
	后面开始往回递归的，可以在输入w,d后直接开始计算前面的，
	用滚动数组的方法减少对重量和d[]的空间消耗，具体代码如下：
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 15000
int dp[X];
int main()
{
	freopen("poj3624.in","r",stdin);
	freopen("poj3624.out","w",stdout);
	int n,m,w,d;
	while(cin>>n>>m)
	{
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&w,&d);
			for(int j=m;j>=0;j--)	//核心代码
				if(j>=w)
					dp[j] = max(dp[j],dp[j-w]+d);
		}
		cout<<dp[m]<<endl;
	}

	return 0;
}