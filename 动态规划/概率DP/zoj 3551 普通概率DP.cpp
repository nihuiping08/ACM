/*
dp[i]表示现在存在i个吸血鬼要达成目标（全为吸血鬼）天数的数学期望
假如现在再增加一天，这一天可能会增加一个吸血鬼，
p1*（dp[i+1]+1）表示接下来的一天增加了一个吸血鬼，
所以为(dp[i+1]+1),
还有一种可能就是没有增加吸血鬼，概率自然是（1-p1）
dp[i]+1表示接下来的一天没有增加吸血鬼，但向后推移了一天
因此dp[i]这个状态可以转移到
dp[i+1]+1,概率为p1
dp[i]+1 概率为（1-p1）
所以dp[i]=(dp[i+1]+1)*p1+(dp[i]+1)*(1-p1);
p1是有i个吸血鬼再增加一个的概率
就是说一个人和一个吸血鬼相遇，且人成功变成吸血鬼的概率
为（n-i）*i*p/(C(n,2)),即2*(n-i)*i*p/((n-1)*n)
*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 100005;

double dp[X],p;
int n;

int main()
{
	int ncase;
	cin>>ncase;
	while(ncase--)
	{
		cin>>n>>p;
		dp[n] = 0;
		for(long long i=n-1;i>0;i--)
			dp[i] = dp[i+1]+(n-1)/((n-i)*p);
		printf("%.3lf\n",dp[1]);
	}
	return 0;
}
