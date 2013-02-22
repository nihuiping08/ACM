/*

��Ŀ��
	���ڵ��ϵ�ľ���ĸ��������档

������
	���Դӷ���д�����룬����ǰ���ľ��������ľ���ཻ�Ļ������ľ���������������档
	�ж��߶��Ƿ��ཻ�Ļ��������ÿ���ʵ��Ϳ����ų���������֤

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
double det(point a,point b,point o)	//��oΪ�����������Ϊx,b�������Ĳ��
{
	return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
bool direction(point a,point b,point o)//o,a,b���㹲��ʱ����o�Ƿ����߶�ab������
{
	if(o.x>min(a.x,b.x)&&o.x<max(a.x,b.x))
		return true;
	return false;
}
bool intersect(point a,point b,point c,point d)
{
	double d1 = det(a,b,c);		//������
	double d2 = det(a,b,d);
	double d3 = det(c,d,a);
	double d4 = det(c,d,b);
	if(d1*d2<0&&d3*d4<0)	//����ʵ��
		return true;
	else if(d1==0&&direction(a,b,c))//�����ų�����
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