/*
题意：
	给出价值分别为1到6的东西的各个数量，问你能不能平分这些东西
分析：
	多重背包问题，因为数据不大，最大才总共20000个物品，可以采用二进制压缩dp的方法
	做，状态转移方程很容易写出：
	dp[i][j] = max(dp[i-1][j],dp[i][j-d[i]]+d[i])，，然后用01背包的思想，压缩空间为O(n)
	状态转移方程为dp[j] = max(dp[j],dp[j-d[i]]+d[i])，
	注意到此时若全部物品都为6的话，当然要把dp开到120002(其实应该可以只开到60002就行)才不会
	PE（我就贡献了一次了）。另外注意到可以平分的话，总和必为2的倍数
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 120010
int d[7],dp[X],a[X],n;
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int cnt = 0,temp,cur;
	while(cin>>d[1]>>d[2]>>d[3]>>d[4]>>d[5]>>d[6],d[6]||d[1]||d[2]||d[3]||d[4]||d[5])
	{
		n = 0;
		int sum = d[1]+d[2]*2+d[3]*3+d[4]*4+d[5]*5+d[6]*6;
		printf("Collection #%d:\n",++cnt);
		if(sum%2)
			cout<<"Can't be divided."<<endl<<endl;
		else
		{
			for(int i=1;i<=6;i++)
			{
				temp = 1;
				cur = d[i];
				while(cur-temp>0)	//二进制压缩
				{
					a[n++] = temp*i;
					cur-=temp;
					temp*=2;
				}
				a[n++] = cur*i;		//注意到还有可能还没有被除完的可能
			}
			sum/=2;
			memset(dp,0,sizeof(dp));
			for(int i=0;i<n;i++)
				for(int j=sum;j>=a[i];j--)
					dp[j] = max(dp[j],dp[j-a[i]]+a[i]);
			if(dp[sum]==sum)
				printf("Can be divided.\n\n");
			else
				cout<<"Can't be divided."<<endl<<endl;
		}
	}
	return 0;
}
