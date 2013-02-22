/*

题目：
	扔在地上的木棍哪根是在上面。

分析：
	可以从方面写出代码，即若前面的木棍与后面的木棍相交的话，则此木棍不可能在最上面。
	判断线段是否相交的话，可以用跨立实验和快速排斥试验来验证

*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
#define X 100010
struct point
{
	double x,y;
};
point s[X],e[X];
int n;
bool use[X];
double det(point a,point b,point o)	//以o为起点而两个结点为x,b的向量的叉积
{
	return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
bool direction(point a,point b,point o)//o,a,b三点共线时，点o是否在线段ab的上面
{
	if(o.x>min(a.x,b.x)&&o.x<max(a.x,b.x))
		return true;
	return false;
}
bool intersect(point a,point b,point c,point d)
{
	double d1 = det(a,b,c);		//计算叉积
	double d2 = det(a,b,d);
	double d3 = det(c,d,a);
	double d4 = det(c,d,b);
	if(d1*d2<0&&d3*d4<0)	//跨立实验
		return true;
	else if(d1==0&&direction(a,b,c))//快速排斥试验
		return true;
	else if(d2==0&&direction(a,b,d))
		return true;
	else if(d3==0&&direction(c,d,a))
		return true;
	else if(d4==0&&direction(c,d,b))
		return true;
	else
		return false;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	while(cin>>n,n)
	{
		memset(use,false,sizeof(use));
		for(int i=1;i<=n;i++)
			scanf("%lf%lf%lf%lf",&s[i].x,&s[i].y,&e[i].x,&e[i].y);
		cout<<"Top sticks: ";
		bool flag = false;
		for(int i=1;i<n;i++)
		{
			for(int j=i+1;j<=n;j++)
				if(intersect(s[i],e[i],s[j],e[j]))
				{
					use[i] = true;
					break;
				}
		}
		for(int i=1;i<=n;i++)
			if(!use[i])
			{
				if(flag)
					printf(", %d",i);
				else
				{
					flag = true;
					printf("%d",i);
				}
			}
			cout<<"."<<endl;
	}

	return 0;
}