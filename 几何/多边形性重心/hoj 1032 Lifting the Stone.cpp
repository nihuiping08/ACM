/*
����������漰��������������Ĺ���ѧ����ʱ�ر����ã��������Ի������������ֵ����˹���ַ���Ҳ������
���������ʽ�����������ɶ���v1 ,v2 ��v3 ����������� T���κ����������ڲ��ĵ�p ����д�ɶ���ļ�Ȩ�ͣ�
p = ��1*a+��2*b+��3*c,�����1����2����3��������꣬��1+��2+��3 = 1��
���Զ���ε������ʽ���Ա�Ϊ��
gx = ((x1+x2+x3)*s1+(x1+x3+x4)*s2+(x1+x4+x5)*s3+...+(x1+xn-1+xn)*sn-2)/(S*3);
gyͬ��siΪ����i+1,i+2��1��ɵ������ε�������������ε������ʽΪ�˼������������ò�����㣬ע
�⵽����Ľ��Ϊ�����ε��������*2


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
double Area()		//���������ε����
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
			tarea += area;	//�����ܵ����
			sum_x += (p0.x+p1.x+p2.x)*area;
			sum_y += (p0.y+p1.y+p2.y)*area;
			p1 = p2;
		}
		printf("%.2lf %.2lf\n",sum_x/tarea/3,sum_y/tarea/3);
	}

	return 0;
}