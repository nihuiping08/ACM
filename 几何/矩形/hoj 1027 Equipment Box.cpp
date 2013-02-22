/*

题目：
	问矩形中能否再套进一个矩形
分析：
	计算几何类，考虑矩形可以斜着放进的特殊情况，具体看我下的那份题解

*/
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
	if(a<x)
		return false;
	if(a>=x&&b>=y)
		return true;
	double dis = sqrt(x*x+y*y);
	double p = asin(a/dis);
	double q = asin(x/dis);
	double sita = p-q;
	double len = y*cos(sita)+x*sin(sita);
	if(len<=b)
		return true;
	return false;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t;
	cin>>t;
	double a,b,x,y;
	while(t--)
	{
		cin>>a>>b>>x>>y;
		if(!check(a,b,x,y))
			printf("Box cannot be dropped.\n");
		else
			printf("Escape is possible.\n");
	}

	return 0;
}