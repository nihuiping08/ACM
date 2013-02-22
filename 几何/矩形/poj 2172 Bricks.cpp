/*

跟hoj1028 // poj1380基本一样，只不过这题是三维的而已，就是多了两个判断，
画图就可以解决了（详情看hoj1028）

*/
#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
bool check(double a,double b,double x,double y)
{
	if(a*b<x*y)
		return false;
	if(a>b)
		swap(a,b);
	if(x>y)
		swap(x,y);
	if(a>=x&&b>=y)
		return true;
	if(a<x)
		return false;
	double dis = sqrt(x*x+y*y);
	double p = asin(a/dis);
	double q = asin(x/dis);
	double t = p-q;
	double len = x*sin(t)+y*cos(t);
	if(len<=b)
		return true;
	return false;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	double a,b,c,d,e;
	cin>>a>>b>>c>>d>>e;
	if(check(d,e,a,b)||check(d,e,a,c)||check(d,e,b,c))//随便有一个面可以放下的话
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
	return 0;
}