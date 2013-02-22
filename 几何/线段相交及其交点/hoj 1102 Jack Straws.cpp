/*

题意：首先给出一个n，表示共有n条边，下面n行(编号1-n)每行给出4个数分别表示起始点的横纵坐标以
及终止点的横纵坐标。接下来的若干行为查询条件，要你输出查询的两条边是否有关系(即直接相交或间
接相交)。如果点在线上也算相交

*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define X 15
struct node
{
	int x,y;
}p[X][2];
int n;
bool con[X][X];
bool equal(node x,node y)
{
	if(x.x==y.x&&x.y==y.y)
		return true;
	return false;
}
int cross(node a,node b,node c)	//相当于求完斜率且变形之后比较斜率的大小，大的斜率在上方
{		//叉积，结果大于0则AB在AC的顺时针方向上，小于0在逆时针方向上，等于0则共线
	int x1 = b.x-a.x;
	int y1 = b.y-a.y;
	int x2 = c.x-a.x;
	int y2 = c.y-a.y;
	return (x1*y2-x2*y1);
}
int dot(node a,node b,node c)
{		//点积，结果大于0则夹角小于90度，小于0则大于90度，等于零则垂直
	int x1 = b.x-a.x;	//相当于两向量之间的点乘关系
	int y1 = b.y-a.y;
	int x2 = c.x-a.x;
	int y2 = c.y-a.y;
	return (x1*x2+y1*y2);
}
bool segcrosssimple(int x,int y)//跨立检验
{
	if(equal(p[x][0],p[y][0])||equal(p[x][1],p[y][1]))	//若起点或终点相同的话相交
		return true;
	if(equal(p[x][0],p[y][1])||equal(p[x][1],p[y][0]))//若一个线段的起点落在另一端线段的终点
		return true;
	int d1 = cross(p[x][0],p[x][1],p[y][0]);//利用叉积原理判断另外一线段的两点是否在另一线段的两侧
	int d2 = cross(p[x][0],p[x][1],p[y][1]);
	int d3 = cross(p[y][0],p[y][1],p[x][0]);
	int d4 = cross(p[y][0],p[y][1],p[x][1]);
	if(d1*d2<0&&d3*d4<0)		//一线段的两端点在另一线段的两侧，相交
		return true;
	if(!d1&&dot(p[y][0],p[x][0],p[x][1])<0) //如果线段共线，判断点是否在线段上
		return true;
	if(!d2&&dot(p[y][1],p[x][0],p[x][1])<0)
		return true;
	if(!d3&&dot(p[x][0],p[y][0],p[y][1])<0)
		return true;
	if(!d4&&dot(p[x][0],p[y][0],p[y][1])<0)
		return true;
	return false;
}
void floyd()		//连通性传递闭包
{				//若当前i和j没有通路的话，若从i到k，k有通路到j，则i到j有通路
	int i,j,k;
	for(k=1;k<=n;k++)
		for(i=1;i<=n;i++)
			if(con[i][k])
				for(j=1;j<=n;j++)
					if(con[k][j])
						con[i][j] = true;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	while(cin>>n,n)
	{
		for(int i=1;i<=n;i++)
			scanf("%d%d%d%d",&p[i][0].x,&p[i][0].y,&p[i][1].x,&p[i][1].y);
		for(int i=1;i<=n;i++)
			for(int j=1;j<n;j++)
				con[i][j] = con[j][i] = segcrosssimple(i,j);
		floyd();
		int x,y;
		while(scanf("%d%d",&x,&y),x||y)
			if(con[x][y])
				printf("CONNECTED\n");
			else
				printf("NOT CONNECTED\n");
	}
	return 0;
}