/*
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
#define esp 1e-8
struct point
{
	double x,y;
};
struct Line
{
	point start,end;
}line[2];

bool zero(double x)			//�ж��Ƿ�Ϊ0
{
	return abs(x)<esp;
}

double xmult(point o,point a,point b)	//������
{
	return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}

bool dot_online(Line a,Line b)	//�е��Ƿ����߶���,�����˵�
{
	if(zero(xmult(a.start,b.start,b.end))==0||zero(xmult(b.end,a.start,b.end))==0)
		return true;
	return false;
}

double det(double x1,double y1,double x2,double y2)
{
	return x1*y2-x2*y1;
}

bool parallel(Line a,Line b)	//�ж���ֱ���Ƿ�ƽ��
{
	return zero((a.start.x-a.end.x)*(b.start.y-b.end.y)-(b.start.x-b.end.x)*(a.start.y-a.end.y))==0;
}

point intersect(double a1,double b1,double c1,double a2,double b2,double c2)
{
	point ret;
	ret.y = (a1*c2-a2*c1)/(a2*b1-a1*b2);
	if(zero(a2)==0)
		ret.x = -(b1*ret.y+c1)/a1;
	else
		ret.x = -(b2*ret.y+c2)/a2;
	return ret;
}

int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t;
	cin>>t;
	while(t--)
	{
		cin>>line[0].start.x>>line[0].start.y>>line[0].end.x>>line[0].end.y
			>>line[1].start.x>>line[1].start.y>>line[1].end.x>>line[1].end.y;

	}
	return 0;
}
*/
/*

��Ŀ��
	�����߶��Ƿ��غϡ�ƽ�л��ཻ

������
	���ò���������������������ǿ������ж��Ƿ���ƽ�еģ�ֻ�轫ÿһ���߶���������������һ��
	������������㣬��Ϊ0��ƽ�л��غϣ��ж��Ƿ��غϣ�ֻ��������һ���������������һ������һ����
	��һ����ɵ�������������㣬Ϊ0��Ϊ�غϡ�
	��ƽ�еĻ�����ô�ڱ�������һ�����㣬���������߶ηֱ����ڵ�ֱ��(ax+by+c=0)��Ȼ���������̽��
	x,y����

*/
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
struct point	//��
{
	int x,y;
};
struct line		//��
{
	point a,b;
}Line[2];
int det(int x1,int y1,int x2,int y2)//�������
{
	return x1*y2-x2*y1;
}
bool parallel(line u,line v)	//�ж��Ƿ�ƽ��
{
	if(det( u.b.x-u.a.x , u.b.y-u.a.y , v.b.x-v.a.x , v.b.y-v.a.y )==0)
		return true;
	return false;
}
bool same_line(line u,line v)	//�ж��Ƿ��غ�
{
	if(det( v.a.x-u.a.x , v.a.y-u.a.y ,u.b.x-u.a.x , u.b.y-u.a.y )==0)
		return true;
	return false;
}
void cal(int a1,int b1,int c1,int a2,int b2,int c2)//���߶�����ֱ�ߵ�һ�㷽�̷ֱ��3��ϵ��
{
	double x,y;
	y = (a1*c2-c1*a2*1.0)/(a2*b1-a1*b2);
	if(a1==0)
		x = (-c2-b2*y)/a2;
	else
		x = (-c1-b1*y)/a1;
	printf("POINT %.2lf %.2lf\n",x,y);
}
void intersect(line u,line v)	//�ཻ�����
{
	int a1 = u.b.y-u.a.y;
	int b1 = u.a.x-u.b.x;
	int c1 = -u.b.y*b1-u.b.x*a1;

	int a2 = v.b.y-v.a.y;
	int b2 = v.a.x-v.b.x;
	int c2 = -v.b.y*b2-v.b.x*a2;
	cal(a1,b1,c1,a2,b2,c2);
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t;
	cin>>t;
	cout<<"INTERSECTING LINES OUTPUT"<<endl;
	while(t--)
	{
		for(int i=0;i<2;i++)
			cin>>Line[i].a.x>>Line[i].a.y>>Line[i].b.x>>Line[i].b.y;
		if(parallel(Line[0],Line[1]))
		{
			if(same_line(Line[0],Line[1]))
				cout<<"LINE"<<endl;
			else
				cout<<"NONE"<<endl;
		}
		else
			intersect(Line[0],Line[1]);
	}
	cout<<"END OF OUTPUT"<<endl;
	return 0;
}