/*

题目：
	墙壁的点之间的中点有门，在正方形内有一处宝藏，问如何穿越最少的门到达该处

分析：
	由于形成的是一个凸包，所以宝藏和线段的连线与其他直线相交的的条数即为需要穿越的次数。
	而判断线段相交用跨立实验和快速排斥实验即可。枚举所有的中点与宝藏的连线组成的线段与其他
	的直线是否相交即可。
	（不知道是不是我弄错了题意，感觉枚举中点时的做法是错的。。。而此前我的做法应该是对的，
	但是狂WA，另外由于忽略掉1时同样要输出Number of doors = ，搞到我狂WA。。。。）

*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
#define esp 1e-8
bool use[35];

struct point{	//点的坐标
	double x,y;
}s[110];

struct line{	//直线的坐标
	point a,b;
}p[35];

int dcmp(double x){	//判断是否为0
	if(abs(x)<esp)
		return 0;
	return x>0?1:-1;
}

double det(point a,point b,point o){	//三个点的叉积
	return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}

bool dot(point a,point b,point o){		//判断点是否在线段上
	if(dcmp(min(a.x,b.x)-o.x)<=0&&dcmp(max(a.x,b.x)-o.x)>=0)
		return true;
	return false;
}

bool intersect(point a,point b,point c,point d){
	int d1 = dcmp(det(a,b,c));
	int d2 = dcmp(det(a,b,d));
	int d3 = dcmp(det(c,d,a));
	int d4 = dcmp(det(c,d,b));
	if((d1^d2)==-2&&(d3^d4)==-2)//跨立实验
		return true;
	else if(d1==0&&dot(a,b,c))	//快速排斥试验
		return true;
	else if(d2==0&&dot(a,b,d))
		return true;
	else if(d3==0&&dot(c,d,a))
		return true;
	else if(d4==0&&dot(c,d,b))
		return true;
	else
		return false;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,ret;
	cin>>n;
	ret = 0;
	for(int i=1;i<=n;i++){
		cin>>p[i].a.x>>p[i].a.y>>p[i].b.x>>p[i].b.y;
		s[++ret] = p[i].a;
		s[++ret] = p[i].b;
	}

	int ans = 10000000,cnt = 0;
	point q;

	cin>>q.x>>q.y;
	if(n==0){
		printf("Number of doors = %d\n",1);
		return 0;
	}
	
	for(int i=1;i<=ret;i++){	//枚举所有的中点
		cnt = 1;
		for(int j=1;j<=n;j++){
			if((s[i].x==p[j].a.x&&s[i].y==p[j].a.y)||(s[i].x==p[j].b.x&&s[i].y==p[j].b.y))
				continue;
			if(intersect(q,s[i],p[j].a,p[j].b))
				cnt++;
		}
		ans = min(cnt,ans);	//更新
	}
	printf("Number of doors = %d\n",ans);
	return 0;
}