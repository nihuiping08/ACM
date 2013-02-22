/*

���Լ��ϵͳballman-ford����

���⣺����n��������m��Լ����ʽ asi + asi+1 + .... + asi+ni < ki or >b ki ,�����ж��Ƿ�����Ž�
	������m��Լ����ʽ��
 
��⣺
	���� asi + asi+1 + ....... + asi + n < ki or > ki,��Ϊai��ki��Ϊ������sum[n] Ϊ ����ai
	��ǰn���ͣ������ת��Ϊ sum[si+n] - sum[si-1] <= ki -1 or sum[si-1] - sum[si+n] <= -1-ki ,
	���������ת��Ϊ���Լ�������������˲��Լ��ϵͳ���������ʡ���һ���Ǵ����ֻ����>=��
	��<=���ڶ����ǲ��Լ��ϵͳ�Ľ����ƽ�ơ���ʼ�������ʱ���ûע�⵽������>��<��

*/

/*
	
	sum[si+ni]-sum[si-1]>w,
	��sum[si-1]-sum[si+ni]<=-w-1
	sum[si+ni]-sum[si-1]<w,
	��sum[si+ni]-sum[si-1]<=w-1

*/
#include <iostream>
#include <cstdio>
using namespace std;
#define X 200
#define INF 0xfffffff
struct node
{
	int u,v,weight;
}p[X*X/2];
int dis[X],m,n;
void add(int i,int u,int v,int w)
{
	p[i].u = u;
	p[i].v = v;
	p[i].weight = w;
}
void bellman_ford()
{
	for(int i=1;i<=n;i++)
		dis[i] = INF;
	dis[1] = 0;
	int x,y;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			x = p[j].u;
			y = p[j].v;
			dis[y] = min(dis[y],dis[x]+p[j].weight);	//��ÿһ���߽����ɳڲ���
		}
	}
	for(int j=1;j<=m;j++)
	{
		x = p[j].u;
		y = p[j].v;
		if(dis[y]>dis[x]+p[j].weight)			//�����û�и�������
		{
			cout<<"successful conspiracy"<<endl;
			return;
		}
	}
	cout<<"lamentable kingdom"<<endl;
	return;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int a,b,w;
	char ch[3];
	while(cin>>n,n)
	{
		cin>>m;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%s%d",&a,&b,ch,&w);
			b += a;
			b++;			//��Ϊsum[si+ni]-sum[si-1]>w,��<w��si��1��ʼ������Ҫ�������±��һ
			if(ch[0]=='g')
				add(i,b,a,-w-1);	//sum[si+ni]-sum[si-1]>w ��sum[si-1]-sum[si+ni]<=-w-1
			else
				add(i,a,b,w-1);	//sum[si+ni]-sum[si-1]<w,��sum[si+ni]-sum[si-1]<=w-1
		}
		bellman_ford();
	}
	return 0;
}