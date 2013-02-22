/*
������
	(A+C*x)mod(2^k)=B,��A+C*x=y*2^k+B,ԭ����(A+C*x)mod(2^k)������ΪB���������Ĳ���
	�а���y*2^k�����Ի���ΪC*x-y*2^k = B-A,�ٸ�����չ��ŷ������㷨�������
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
			k1 = k1*(b-a)/d;/*����ax-by=c����ʽ��������ax+by=c����ʽ
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