/*
面积坐标在涉及到三角形子区域的工程学问题时特别有用，经常可以化简解析积分求值，高斯积分法表也常以面
积坐标的形式给出。考虑由顶点v1 ,v2 和v3 定义的三角形 T，任何在三角形内部的点p 都能写成顶点的加权和：
p = λ1*a+λ2*b+λ3*c,这里λ1，λ2，λ3是面积坐标，λ1+λ2+λ3 = 1。
所以多边形的面积公式可以变为：
gx = ((x1+x2+x3)*s1+(x1+x3+x4)*s2+(x1+x4+x5)*s3+...+(x1+xn-1+xn)*sn-2)/(S*3);
gy同理，si为顶点i+1,i+2与1组成的三角形的面积，而三角形的面积公式为了减少误差，可以利用叉积运算，注
意到叉积的结果为三角形的有向面积*2


*/
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
#define X 1000010
struct point
{
	double x,y;
};
point p0,p1,p2;
double Area()		//计算三角形的面积
{
	return ((p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y))/2;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,t;
	cin>>t;
	while(t--)
	{
		cin>>n;
		cin>>p0.x>>p0.y;
		cin>>p1.x>>p1.y;
		double area,tarea = 0,sum_x = 0,sum_y = 0;
		for(int i=2;i<n;i++)
		{
			scanf("%lf%lf",&p2.x,&p2.y);
			area = Area();
			tarea += area;	//计算总的面积
			sum_x += (p0.x+p1.x+p2.x)*area;
			sum_y += (p0.y+p1.y+p2.y)*area;
			p1 = p2;
		}
		printf("%.2lf %.2lf\n",sum_x/tarea/3,sum_y/tarea/3);
	}

	return 0;
}