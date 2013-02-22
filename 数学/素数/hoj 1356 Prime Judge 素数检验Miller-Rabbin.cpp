/*
题目大意就是给出一个不超过2^31的数，来判断它是否为素数，对于此题的规模，
一般的素性检测显然不行，要用到Miller rabin, 这个算法主要是基于费尔马小定理，
如果 n 为素数，那么对于小于n的数a有a^(n-1) = 1(mod n) ('='在这里就代表同余符号)。
显然这是一个必要条件，然而只要满足这个条件就基本上是一个素数了，称为‘伪素数’，
正确率为1-(1/4)^m，m用不同的基测试的次数，所以多测试几次就可以保证结果的正确了
*/
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
long long ans;
void power(long long a,long long b,int n)
{//快速幂取模a^b%n
	if(b==1)
	{
		ans = a;
		return;
	}
	power(a,b/2,n);
	if(b%2)
		ans = (ans*ans%n)*a%n;
	else
		ans = ans*ans%n;
}
bool Miller_Rabbin(long long n)
{	//费尔马小定理，如果 n 为素数，那么对于小于n的数a有a^(n-1) = 1(mod n)
	long long a = rand()%(n-1)+1;//随机生成一个小于n的数
	power(a,n-1,n);//a^(n-1) = 1(mod n)
	if(ans%n!=1)
		return false;
	return true;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	long long n;
	while(scanf("%lld",&n)!=EOF)
	{
		int flag = 1;//1表示素数
		int times = 3;//times为每个数进行测试的次数
		if(n<=1)
			flag = 0;
		else if(n==2||n==3)
			flag = 1;
		else
		{
			while(times--&&flag)
				if(!Miller_Rabbin(n))
					flag = 0;
		}
		if(!flag)
			printf("NO\n");
		else
			printf("YES\n");
	}
	return 0;
}