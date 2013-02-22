/*
��Ŀ������Ǹ���һ��������2^31���������ж����Ƿ�Ϊ���������ڴ���Ĺ�ģ��
һ������Լ����Ȼ���У�Ҫ�õ�Miller rabin, ����㷨��Ҫ�ǻ��ڷѶ���С����
��� n Ϊ��������ô����С��n����a��a^(n-1) = 1(mod n) ('='������ʹ���ͬ�����)��
��Ȼ����һ����Ҫ������Ȼ��ֻҪ������������ͻ�������һ�������ˣ���Ϊ��α��������
��ȷ��Ϊ1-(1/4)^m��m�ò�ͬ�Ļ����ԵĴ��������Զ���Լ��ξͿ��Ա�֤�������ȷ��
*/
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
long long ans;
void power(long long a,long long b,int n)
{//������ȡģa^b%n
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
{	//�Ѷ���С������� n Ϊ��������ô����С��n����a��a^(n-1) = 1(mod n)
	long long a = rand()%(n-1)+1;//�������һ��С��n����
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
		int flag = 1;//1��ʾ����
		int times = 3;//timesΪÿ�������в��ԵĴ���
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