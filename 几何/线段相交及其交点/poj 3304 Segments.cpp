/*

��Ŀ��
	����ƽ����n���߶Σ��ж��Ƿ����һ��ֱ�ߣ�ʹ����n���߶���L�ϵ�ͶӰ������һ�������㡣

������
	�������������һ��ֱ�ߣ����ֱ�ߵ�ĳ��ش��ڸ�ֱ�ߵĴ����Ҹô��������е��߶��ཻ��
	��������ת��Ϊ�Ƿ����һ���߶��������߶ξ��ཻ������ֻ��ö��n��ֱ���ж��Ƿ���ֱ��L�ཻ��

	������õķ���Ҳ�Ǽ��㼸���г��õ�����ɢ��˼�롣����֪�������ֻ�ܴ�����ɢ�����ݣ�����û�а�
	����ͨ����������תֱ��L���ֱ��ж��Ƿ��������⡣�������ǿ��Բ�����ɢ����˼�룺��������ֱ��L��
	����n���߶��ཻ�����ǿ��Բ��ý�ֱ��L�ֱ���˳ʱ�����ʱ��ķ�����ת����ת��ʱ�����������n����
	�ξ��ཻ�����ƣ�ֱ���޷���תΪֹ����ô�����ֱ�߻��n���߶��е�ĳ�����Ķ˵��غϡ����������Ǿ�
	����ͨ��ö���������߶ζ˵�ȷ����ֱ�ߣ��Ӷ������������⡣

*/
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
#define esp 1e-8
#define X 110
int n;
struct point		//�������
{
	double x,y;
};
struct node			//�߶�
{
	point start,end;
}p[X];
double dis(point a,point b)//����֮��ľ���
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double cross(point a,point b,point c)//�������Ĳ��
{
	double x1 = c.x-a.x;
	double x2 = b.x-a.x;
	double y1 = c.y-a.y;
	double y2 = b.y-a.y;
	return x1*y2-x2*y1;
}
bool check(point a,point b)	//�ж��Ƿ��������߶��ཻ
{
	if(abs(dis(a,b))<esp)
		return true;	//��ö�����߶��еĶ˵����ܽӽ�(<1e-8)��ʱ�򣬲�����Ϊ��ѡֱ���ж�
	for(int i=1;i<=n;i++)
		if(cross(a,b,p[i].start)*cross(a,b,p[i].end)>0)//��ö�ٵ����߶ε����˾��ڸ�ֱ�ߵ�����
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
				||check(p[i].end,p[j].start)||check(p[i].end,p[j].end))	//�ֱ�ö�������߶ε�����
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