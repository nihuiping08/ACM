/*

���⣺���ȸ���һ��n����ʾ����n���ߣ�����n��(���1-n)ÿ�и���4�����ֱ��ʾ��ʼ��ĺ���������
����ֹ��ĺ������ꡣ��������������Ϊ��ѯ������Ҫ�������ѯ���������Ƿ��й�ϵ(��ֱ���ཻ���
���ཻ)�������������Ҳ���ཻ

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
int cross(node a,node b,node c)	//�൱������б���ұ���֮��Ƚ�б�ʵĴ�С�����б�����Ϸ�
{		//������������0��AB��AC��˳ʱ�뷽���ϣ�С��0����ʱ�뷽���ϣ�����0����
	int x1 = b.x-a.x;
	int y1 = b.y-a.y;
	int x2 = c.x-a.x;
	int y2 = c.y-a.y;
	return (x1*y2-x2*y1);
}
int dot(node a,node b,node c)
{		//������������0��н�С��90�ȣ�С��0�����90�ȣ���������ֱ
	int x1 = b.x-a.x;	//�൱��������֮��ĵ�˹�ϵ
	int y1 = b.y-a.y;
	int x2 = c.x-a.x;
	int y2 = c.y-a.y;
	return (x1*x2+y1*y2);
}
bool segcrosssimple(int x,int y)//��������
{
	if(equal(p[x][0],p[y][0])||equal(p[x][1],p[y][1]))	//�������յ���ͬ�Ļ��ཻ
		return true;
	if(equal(p[x][0],p[y][1])||equal(p[x][1],p[y][0]))//��һ���߶ε����������һ���߶ε��յ�
		return true;
	int d1 = cross(p[x][0],p[x][1],p[y][0]);//���ò��ԭ���ж�����һ�߶ε������Ƿ�����һ�߶ε�����
	int d2 = cross(p[x][0],p[x][1],p[y][1]);
	int d3 = cross(p[y][0],p[y][1],p[x][0]);
	int d4 = cross(p[y][0],p[y][1],p[x][1]);
	if(d1*d2<0&&d3*d4<0)		//һ�߶ε����˵�����һ�߶ε����࣬�ཻ
		return true;
	if(!d1&&dot(p[y][0],p[x][0],p[x][1])<0) //����߶ι��ߣ��жϵ��Ƿ����߶���
		return true;
	if(!d2&&dot(p[y][1],p[x][0],p[x][1])<0)
		return true;
	if(!d3&&dot(p[x][0],p[y][0],p[y][1])<0)
		return true;
	if(!d4&&dot(p[x][0],p[y][0],p[y][1])<0)
		return true;
	return false;
}
void floyd()		//��ͨ�Դ��ݱհ�
{				//����ǰi��jû��ͨ·�Ļ�������i��k��k��ͨ·��j����i��j��ͨ·
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