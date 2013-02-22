/*

分析：
	比较容易理解，如果光线最优的话是可以认为至少与某两个点相切的，因为如果不和某两个点相切，
	我们可以将光线进行平移和旋转使其至少和某两个点相切，而且结果不会变差。

    于是我们可以枚举任意两个顶点确定一条直线作为光线的路径，之后只要看这条光线最多能够
	射多远即可。一个可行的思路就是首先判定这两个顶点及以前的光线是否在管子内，如果在管
	子内，再依次去判定光线最远能射到哪里。判定光线是否在管子内可以判定光线与每对顶点的
	纵截面的交点是否在管子内。

*/
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
#define X 50
#define esp 1e-8
int n;
struct point
{
	double x,y;
}p[X];
int dcomp(double x)		//有精度误差，若小于esp，认为是等于0
{
	if(abs(x)<esp)
		return 0;
	else if(x>0)
		return 1;
	else
		return -1;
}
double det(double x1,double y1,double x2,double y2)//叉积运算
{
	return x1*y2-x2*y1;
}
double getx(double x1,double x2,double t1,double t2)
{
	return (abs(t2)*x1+abs(t1)*x2)/(abs(t1)+abs(t2));
}
double cal(int k1,int k2)	//计算最远x的距离
{
	if(p[k1].x>p[k2].x)		//当后者的x坐标小于前者的坐标时，交换
		swap(k1,k2);
	
	double x1 = p[k1].x;	//方便写代码
	double y1 = p[k1].y;

	double x2 = p[k2].x;
	double y2 = p[k2].y;
	
	double t1,t2;
	if(k2>n)
		k2 -= n;

	for(int i=0;i<k2;i++)		//先枚举上面在k2之前的所有的点，若有相交（不是相切），直接返回
	{
		t1 = det(x2-x1,y2-y1,p[i].x-x1,p[i].y-y1);	//上面的点与要枚举的两个点（即枚举的直线）的叉积
		t2 = det(x2-x1,y2-y1,p[i].x-x1,p[i].y-1-y1);//下面的点
		
		if(dcomp(t1)*dcomp(t2)>0)		//说明上下的点均在直线的同一侧，那么该直线不可能有最大x值
			return p[1].x;
	}
	double t = x2;
	for(int i=k2+1;i<n;i++)		//k2之前所有的点均满足条件时，枚举后面的点，算出并返回最大x值
	{
		t1 = det(x2-x1,y2-y1,p[i-1].x-x1,p[i-1].y-y1);//计算上面相邻的两点分别与(x1,y1)组成的向量与直线的叉积
		t2 = det(x2-x1,y2-y1,p[i].x-x1,p[i].y-y1);
		if(dcomp(t1)*dcomp(t2)<0)		//若上面的相邻两点在直线的两侧，返回x值
			return t = getx(p[i-1].x,p[i].x,t1,t2);	//算出x值

		t1 = det(x2-x1,y2-y1,p[i-1].x-x1,p[i-1].y-1-y1);//计算下面相邻的两点分别与(x1,y1)组成的向量与直线的叉积
		t2 = det(x2-x1,y2-y1,p[i].x-x1,p[i].y-1-y1);
		if(dcomp(t1)*dcomp(t2)<0)		//若下面的相邻的两点在直线的两侧，返回x值
			return t = getx(p[i-1].x,p[i].x,t1,t2);

		t1 = det(x2-x1,y2-y1,p[i].x-x1,p[i].y-y1);//若上面的点与下面的点在同侧，返回
		if(dcomp(t1)*dcomp(t2)>0)
			return t;

		t = p[i].x;
	}
	return t;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	while(cin>>n,n)
	{
		for(int i=0;i<n;i++)
			cin>>p[i].x>>p[i].y;
		for(int i=n;i<2*n;i++)
		{
			p[i].x = p[i-n].x;
			p[i].y = p[i-n].y-1;
		}

		double ans = p[1].x;
		for(int i=0;i<2*n;i++)	//枚举所有的点与点组成的直线所能到达的最大x值
			for(int j=i+1;j<2*n;j++)
				if(i!=j-n)
					ans = max(ans,cal(i,j));//更新ans

		if(dcomp(ans-p[n-1].x)>=0)
			cout<<"Through all the pipe."<<endl;
		else
			printf("%.2lf\n",ans);
	}

	return 0;
}