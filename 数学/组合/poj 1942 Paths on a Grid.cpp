/*

简单的组合问题

题意:一个N*M的网格,只能在网格的边上向上或向右走,求从左下角走到右上角的方案数.

分析:一共要走N+M步,其中M步向右,N步向上.因此方案数即C(N+M,N).


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