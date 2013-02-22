/*

题目：
	给定平面上n条线段，判断是否存在一条直线，使得这n条线段在L上的投影至少有一个公共点。

分析：
	假设存在这样的一条直线，则该直线的某点必存在该直线的垂线且该垂线与所有的线段相交，
	所以问题转化为是否存在一条线段与所有线段均相交。我们只需枚举n条直线判断是否与直线L相交。

	这里采用的方法也是计算几何中常用到得离散化思想。我们知道计算机只能处理离散的数据，我们没有办
	法来通过连续的旋转直线L来分别判定是否满足题意。但是我们可以采用离散化的思想：假设任意直线L分
	别于n条线段相交，我们可以采用将直线L分别向顺时针和逆时针的方向旋转，旋转的时候必须满足于n条线
	段均相交的限制，直到无法旋转为止。那么，最后直线会和n条线段中的某两条的端点重合。这样，我们就
	可以通过枚举任意两线段端点确定的直线，从而对问题进行求解。

*/
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
#define esp 1e-8
#define X 110
int n;
struct point		//点的坐标
{
	double x,y;
};
struct node			//线段
{
	point start,end;
}p[X];
double dis(point a,point b)//两点之间的距离
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double cross(point a,point b,point c)//两向量的叉积
{
	double x1 = c.x-a.x;
	double x2 = b.x-a.x;
	double y1 = c.y-a.y;
	double y2 = b.y-a.y;
	return x1*y2-x2*y1;
}
bool check(point a,point b)	//判断是否与所有线段相交
{
	if(abs(dis(a,b))<esp)
		return true;	//当枚举两线段中的端点距离很接近(<1e-8)的时候，不能作为待选直线判定
	for(int i=1;i<=n;i++)
		if(cross(a,b,p[i].start)*cross(a,b,p[i].end)>0)//若枚举到的线段的两端均在该直线的两端
			return false;
	return true;
}
int main()	
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);		
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>p[i].start.x>>p[i].start.y>>p[i].end.x>>p[i].end.y;
		if(n==1||n==2)
		{
			cout<<"Yes!"<<endl;
			continue;
		}
		bool flag = true;
		for(int i=1;i<=n&&flag;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				if(check(p[i].start,p[j].start)||check(p[i].start,p[j].end)
				||check(p[i].end,p[j].start)||check(p[i].end,p[j].end))	//分别枚举所有线段的两端
				{
					flag = false;
					cout<<"Yes!"<<endl;
					break;
				}
			}
		}
		if(flag)
			cout<<"No!"<<endl;
	}

	return 0;
}