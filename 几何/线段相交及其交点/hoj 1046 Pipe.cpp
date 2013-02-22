/*

������
	�Ƚ�������⣬����������ŵĻ��ǿ�����Ϊ������ĳ���������еģ���Ϊ�������ĳ���������У�
	���ǿ��Խ����߽���ƽ�ƺ���תʹ�����ٺ�ĳ���������У����ҽ�������

    �������ǿ���ö��������������ȷ��һ��ֱ����Ϊ���ߵ�·����֮��ֻҪ��������������ܹ�
	���Զ���ɡ�һ�����е�˼·���������ж����������㼰��ǰ�Ĺ����Ƿ��ڹ����ڣ�����ڹ�
	���ڣ�������ȥ�ж�������Զ���䵽����ж������Ƿ��ڹ����ڿ����ж�������ÿ�Զ����
	�ݽ���Ľ����Ƿ��ڹ����ڡ�

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
int dcomp(double x)		//�о�������С��esp����Ϊ�ǵ���0
{
	if(abs(x)<esp)
		return 0;
	else if(x>0)
		return 1;
	else
		return -1;
}
double det(double x1,double y1,double x2,double y2)//�������
{
	return x1*y2-x2*y1;
}
double getx(double x1,double x2,double t1,double t2)
{
	return (abs(t2)*x1+abs(t1)*x2)/(abs(t1)+abs(t2));
}
double cal(int k1,int k2)	//������Զx�ľ���
{
	if(p[k1].x>p[k2].x)		//�����ߵ�x����С��ǰ�ߵ�����ʱ������
		swap(k1,k2);
	
	double x1 = p[k1].x;	//����д����
	double y1 = p[k1].y;

	double x2 = p[k2].x;
	double y2 = p[k2].y;
	
	double t1,t2;
	if(k2>n)
		k2 -= n;

	for(int i=0;i<k2;i++)		//��ö��������k2֮ǰ�����еĵ㣬�����ཻ���������У���ֱ�ӷ���
	{
		t1 = det(x2-x1,y2-y1,p[i].x-x1,p[i].y-y1);	//����ĵ���Ҫö�ٵ������㣨��ö�ٵ�ֱ�ߣ��Ĳ��
		t2 = det(x2-x1,y2-y1,p[i].x-x1,p[i].y-1-y1);//����ĵ�
		
		if(dcomp(t1)*dcomp(t2)>0)		//˵�����µĵ����ֱ�ߵ�ͬһ�࣬��ô��ֱ�߲����������xֵ
			return p[1].x;
	}
	double t = x2;
	for(int i=k2+1;i<n;i++)		//k2֮ǰ���еĵ����������ʱ��ö�ٺ���ĵ㣬������������xֵ
	{
		t1 = det(x2-x1,y2-y1,p[i-1].x-x1,p[i-1].y-y1);//�����������ڵ�����ֱ���(x1,y1)��ɵ�������ֱ�ߵĲ��
		t2 = det(x2-x1,y2-y1,p[i].x-x1,p[i].y-y1);
		if(dcomp(t1)*dcomp(t2)<0)		//�����������������ֱ�ߵ����࣬����xֵ
			return t = getx(p[i-1].x,p[i].x,t1,t2);	//���xֵ

		t1 = det(x2-x1,y2-y1,p[i-1].x-x1,p[i-1].y-1-y1);//�����������ڵ�����ֱ���(x1,y1)��ɵ�������ֱ�ߵĲ��
		t2 = det(x2-x1,y2-y1,p[i].x-x1,p[i].y-1-y1);
		if(dcomp(t1)*dcomp(t2)<0)		//����������ڵ�������ֱ�ߵ����࣬����xֵ
			return t = getx(p[i-1].x,p[i].x,t1,t2);

		t1 = det(x2-x1,y2-y1,p[i].x-x1,p[i].y-y1);//������ĵ�������ĵ���ͬ�࣬����
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
		for(int i=0;i<2*n;i++)	//ö�����еĵ������ɵ�ֱ�����ܵ�������xֵ
			for(int j=i+1;j<2*n;j++)
				if(i!=j-n)
					ans = max(ans,cal(i,j));//����ans

		if(dcomp(ans-p[n-1].x)>=0)
			cout<<"Through all the pipe."<<endl;
		else
			printf("%.2lf\n",ans);
	}

	return 0;
}