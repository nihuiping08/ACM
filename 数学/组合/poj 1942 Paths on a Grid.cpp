/*

�򵥵��������

����:һ��N*M������,ֻ��������ı������ϻ�������,������½��ߵ����Ͻǵķ�����.

����:һ��Ҫ��N+M��,����M������,N������.��˷�������C(N+M,N).


*/
#include <iostream>
using namespace std;
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	long long m,n;
	while(cin>>n>>m,m||n)
	{
		double ans = 1;
		int r = min(m,n);
		n = m+n;
		while(r>0)
			ans = ans*(n--)/(r--);
		cout<<(long long)(ans+0.5)<<endl;
	}
	return 0;
}