/*
分析：
	由于有些物品存在多个，可以用数组逐一保存下，然后用01背包问题求解，
	但是这样太耗时间，会造成time limitted，可以用二进制形式保存拥有多个
	的物品，这样可以考虑完全并且比较省时间
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define X 100005
int dp[X],cash[X];
int main()
{
	freopen("poj1276.in","r",stdin);
	freopen("poj1276.out","w",stdout);
	int total,n,a,b;
	while(cin>>total)
	{
		int cnt = 0;
		memset(dp,0,sizeof(dp));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&a,&b);
			/*for(int j=1;j<=a;j++)//直接逐一保存太耗时间
				cash[++cnt] = b;*/
			for(int j=1;j<=a;j=j*2)
			{	//采用二进制保存方式比较快些(刚学到的)
				cash[++cnt] = b*j;	//有多个物品的存储在数组中
				a = a-j;
			}
			if(a)	//有剩余的
				cash[++cnt] = a*b;
		}
		///////01背包问题求解方法
		for(int j=1;j<=cnt;j++)
			for(int i=total;i>=cash[j];i--)
				dp[i] = max(dp[i],dp[i-cash[j]]+cash[j]);
		cout<<dp[total]<<endl;
	}

	return 0;
}