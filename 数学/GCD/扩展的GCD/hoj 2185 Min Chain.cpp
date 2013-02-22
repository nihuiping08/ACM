/*
������
	��չ��ŷ������㷨��ax+by=gcd(a,b),��gcd(a,b)!=1�����-1����������չ��ŷ������㷨���
	��С��x��y���ɣ�ע�⵽
	������0ʱ������1���1���������-1��
	������1������2���1���������2(��Ϊֱ��a-a+1����)
	�����涼������ʱ��ֱ������չ��ŷ������㷨���x���ڽⷽ�����y��������ֵ��Ӽ�һ����
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
				k1 = c*k1-d*b;	//���x
				k2 = (1-a*k1)/b;//���y
				long long ans = abs(k1)+abs(k2);
				cout<<ans-1<<endl;
			}
		}
	}
	return 0;
}