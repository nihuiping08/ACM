#include <iostream>
using namespace std;
long long gcd(long long a,long long b)
{			//ŷ������㷨
	if(b==0)
		return a;
	return gcd(b,a%b);
}
long long ex_gcd(long long a,long long b,long long &x,long long &y)
{				//��չ��ŷ������㷨����ax+by=c��һ����
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
		r = gcd(a,b);	//�����ax+by=c��a��b�����Լ��r����c%r!=0���޽�
		if(c%r)
			cout<<"Impossible"<<endl;
		else
		{
			a/=r;	//��ax+by=c�е�Լ��r��������������ʽ
			b/=r;
			c/=r;
			ex_gcd(a,b,k1,k2);	//��չ��ŷ������㷨
			t = c*k1/b;
			k1 = c*k1-t*b;
			if(k1<0)
				k1+=b;
			cout<<k1<<endl;
		}
	}
	return 0;
}