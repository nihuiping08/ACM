/*
分析：
	扩展的欧几里德算法，ax+by=gcd(a,b),若gcd(a,b)!=1，输出-1，否则，用扩展的欧几里德算法求出
	最小的x与y即可，注意到
	当存在0时，若有1输出1，否则输出-1；
	当存在1，若有2输出1，否则输出2(因为直接a-a+1即可)
	当上面都不满足时，直接用扩展的欧几里德算法求出x，在解方程求出y，两绝对值相加减一即可
*/
#include <cmath>
#include <iostream>
using namespace std;
long long ex_gcd(long long a,long long b,long long &x,long long &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	long long r = ex_gcd(b,a%b,x,y);
	long long t = x;
	x = y;
	y = t-a/b*y;
	return r;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t;
	cin>>t;
	long long a,b,c = 1,r,k1,k2,d;
	while(t--)
	{
		cin>>a>>b;
		if(b>a)
			swap(a,b);
		if(!b)
		{
			if(a==1)
				cout<<1<<endl;
			else
				cout<<-1<<endl;
		}
		else if(a==2&&b==1)
			cout<<1<<endl;
		else if(b==1)
			cout<<2<<endl;
		else
		{
			r = ex_gcd(a,b,k1,k2);
			if(r!=1)
				cout<<-1<<endl;
			else
			{
				d = k1*c/b;
				k1 = c*k1-d*b;	//求出x
				k2 = (1-a*k1)/b;//求出y
				long long ans = abs(k1)+abs(k2);
				cout<<ans-1<<endl;
			}
		}
	}
	return 0;
}