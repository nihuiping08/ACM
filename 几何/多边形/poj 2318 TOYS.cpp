/*

��Ŀ��
	��ͼ��ʾ������һ�������Լ������ߵ��������꣬�ָ�������������ڵ����꣬��
	�ڼ������������м������

������
	����+��������ֳ��߶ε�λ�ã�Ȼ���ò���жϼ��ɣ������Ӧ�ã�
	p1 = (x1,y1),p2 = (x2,y2),��temp = p1 X p2 = x1*y2-x2*y1,
	��temp>0����p1��p2��˳ʱ�뷽���ϣ�==0���ߣ�<0��Ϊ��ʱ�뷽����

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
long long det(int x1,int y1,int x2,int y2)//�������
{
	return (long long)x1*y2-(long long)x2*y1;//int���ܻ����
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
		if( det( p[mid].x-p[mid].y , p[0].y-p[n+1].y , x-p[mid].y , y-p[n+1].y )<0 )//�����ڻ���������
			down = mid;
		else	//���ڻ�������߻����ڻ�������
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