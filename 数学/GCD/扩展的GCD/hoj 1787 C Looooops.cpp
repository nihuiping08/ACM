/*
分析：
	(A+C*x)mod(2^k)=B,即A+C*x=y*2^k+B,原因是(A+C*x)mod(2^k)的余数为B，被减掉的部分
	中包含y*2^k，可以化简为C*x-y*2^k = B-A,再根据扩展的欧几里德算法即可求出
*/
#include <iostream>
#include <cstdio>
using namespace std;
long long ex_gcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0)
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
	long long k,r,a,b,c,d,k1,k2,f;
	while(scanf("%lld%lld%lld%lld",&a,&b,&c,&k)==4,a||b||c||k)
	{
		f = (long long)1<<k;
		d = ex_gcd(c,f,k1,k2);
		if((b-a)%d)
			cout<<"FOREVER"<<endl;
		else
		{
			k1 = k1*(b-a)/d;/*这是ax-by=c的形式，以下是ax+by=c的形式
							t = c*k1/b;
							k1 = c*k1-t*b;
							if(k1<0)
								k1+=b;
							cout<<k1<<endl*/
			r = f/d;
			k1 = (k1%r+r)%r;
			printf("%lld\n",k1);
		}
	}

	return 0;
}