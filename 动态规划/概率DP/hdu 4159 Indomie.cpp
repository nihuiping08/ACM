/*

题目：
	有n个人在排队，商品的种类只剩下3种，并且其中的两种物品数量不限，另一种的数量有限，现在给出
	数量有限的商品的数量以及前面有几人在排队，问你能够购买该物品的概率是多少

分析：
	组合概率：
	先求出组合数f[i][j]，然后算出不能购买的概率为：
	f[n][s] / (2^s+2^(s-1)*f[n][1]+2^(s-2)*f[n][2]+...+1*f[n][s])极为所求

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 51;

double dp[X][X];
double f[X][X];
int n,m;

int main()
{
	long long q = 1;
	for(int i=0;i<X;i++)
		f[i][0] = 1;
	memset(dp,0,sizeof(dp));
	for(int i=1;i<X;i++)
		for(int j=1;j<=i;j++)
			f[i][j] = f[i-1][j-1]+f[i-1][j];
	for(int i=1;i<X;i++)
		for(int j=0;j<X;j++)
		{
			q = 1;
			double temp = 0;
			for(int k=j;k>=0;k--)
			{
				temp += q*f[i][k];
				q = q<<1;
			}
			dp[i][j] = f[i][j]/temp;
		}
	while(cin>>n>>m)
		printf("%.5lf\n",100-100*dp[n][m]);
	return 0;
}
