/*

题目：
	如图所示，给出一个矩形以及划分线的上下坐标，现给出玩具落下所在的坐标，问
	第几个划分区间有几个玩具

分析：
	二分+叉积，二分出线段的位置，然后用叉积判断即可，叉积的应用：
	p1 = (x1,y1),p2 = (x2,y2),则temp = p1 X p2 = x1*y2-x2*y1,
	若temp>0，则p1在p2的顺时针方向上，==0则共线，<0则为逆时针方向上

*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
#define X 5005
struct node
{
	long long x,y;
}p[X];
int num[X],n,m;
long long det(int x1,int y1,int x2,int y2)//叉积运算
{
	return (long long)x1*y2-(long long)x2*y1;//int可能会溢出
}
void besearch(int x,int y)
{
	int up = n+1;
	int down = 0;
	while(true)
	{
		int mid = (up-down)/2+down;
		if(mid==down)
			break;
		if( det( p[mid].x-p[mid].y , p[0].y-p[n+1].y , x-p[mid].y , y-p[n+1].y )<0 )//若点在划分线右面
			down = mid;
		else	//点在划分线左边或者在划分线上
			up = mid;
	}
	num[down]++;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int x,y;
	bool flag = false;
	while(cin>>n,n)
	{
		if(flag)
			cout<<endl;
		else
			flag = true;
		memset(num,0,sizeof(num));
		cin>>m;
		cin>>p[0].x>>p[0].y>>p[n+1].x>>p[n+1].y;
		for(int i=1;i<=n;i++)
			scanf("%lld%lld",&p[i].x,&p[i].y);
		while(m--)
		{
			cin>>x>>y;
			besearch(x,y);
		}
		for(int i=0;i<=n;i++)
			printf("%d: %d\n",i,num[i]);
	}
	return 0;
}