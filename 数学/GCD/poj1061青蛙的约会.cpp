#include <iostream>
using namespace std;
long long gcd(long long a,long long b)
{			//欧几里德算法
	if(b==0)
		return a;
	return gcd(b,a%b);
}
long long ex_gcd(long long a,long long b,long long &x,long long &y)
{				//扩展的欧几里德算法，求ax+by=c的一个解
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
	long long m,n,x,y,L,a,b,c,r,k1,k2,t;
	while(cin>>x>>y>>m>>n>>L)
	{
		a = n-m;
		b = L;
		c = x-y;
		r = gcd(a,b);	//先求出ax+by=c中a与b的最大公约数r，若c%r!=0，无解
		if(c%r)
			cout<<"Impossible"<<endl;
		else
		{
			a/=r;	//将ax+by=c中的约数r除掉，变成最简形式
			b/=r;
			c/=r;
			ex_gcd(a,b,k1,k2);	//扩展的欧几里德算法
			t = c*k1/b;
			k1 = c*k1-t*b;
			if(k1<0)
				k1+=b;
			cout<<k1<<endl;
		}
	}
	return 0;
}