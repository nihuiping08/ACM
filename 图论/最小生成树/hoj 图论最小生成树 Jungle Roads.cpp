/*
��Ŀ��
	���ϵľ���Ҫ����̵�·��ʹ�÷�������
������
	ʵ����������С��������������prim�㷨��kruskal�㷨��
	���ڸ�ѧkruskal�㷨����������kruskal�㷨���ġ�

	kruskal�㷨��˼����:
	�Ȱ����еı߰��շǽ������У��Ӷ��۲�ÿ�����Ƿ�������ǰ
	�ı���ɻ����ܵĻ��Ͳ�ѡ�����ܵĻ���ѡ�񣬶��ж��Ƿ���
	�ɻ�·�Ļ�����ͨ��ʹ�ò��鼯ʵ��

	���鼯��˼���ǣ�
	{1,2,3},{4,5},{6,7,8},{9},���ñ��ǵ�ǰ���ٵı�ʱ�����˶���Ϊ
	1,4����Ϊ1,4��������ͬ�ļ����У��ʶ�������ɻ�·��������ͬһ
	�����У���1��2����Ϊǰ��϶�1,2,3��ֱ�ӻ��������ӣ������(1,2)
	�ɶ���ʹ��ͼ��ɻ�·���ʶ����������´���ʵ�ֲ��鼯�������(u,v)
	�ı߶���Ϊu[i],v[i],����Ϊlen[i]
	int find_set(int x)
	{
		if(x==union_set[x])
			return x;
		return find_set(union_set[x]);
	}
	������main�����Ｔ��ʵ��
	int ans = 0;
	for(int i=0;i<=cnt;i++)
		union_set[i]=i;
	int x = find_set(u[i]);
	int y = find_set(v[i]);
	if(x!=y)
	{
		union_set[y]=x;
		ans+=len[i];
	}
	�𰸼�Ϊans
*/
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
#define X 150
int union_set[80];//���鼯
typedef struct node
{	//����ṹ��
	int u,v,len;//���㣬���㣬����
}node;
struct node p[X];
int find_set(int x)
{	//���Ҹ�Ԫ�����ڼ���
	if(x==union_set[x])
		return x;
	return find_set(union_set[x]);
}
int cmp(const void *a,const void *b)
{	//ǿתΪ�ṹ�����򣬰����ȵķǽ�����
	struct node *c = (struct node *)a;
	struct node *d = (struct node *)b;
	return c->len-d->len;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n;
	while(cin>>n,n)
	{
		int a,b;
		char ch1,ch2;
		int cnt = 0;
		for(int i=0;i<n-1;i++)
		{
			cin>>ch1>>a;
			for(int j=0;j<a;j++)
			{
				cin>>ch2>>b;
				p[cnt].u = ch1-'A';
				p[cnt].v = ch2-'A';
				p[cnt].len = b;
				cnt++;
			}
		}
		qsort(p,cnt,sizeof(p[0]),cmp);//����
		
		//�տ�ʼ��ʱ����n��ɭ�֣�ÿһ��Ԫ�ؾ�Ϊ�ü��ϵ����
		for(int i=0;i<=cnt;i++)
			union_set[i] = i;
		int ans = 0;
		for(int i=0;i<cnt;i++)
		{
			int x = find_set(p[i].u);//���Ҷ������ڼ������
			int y = find_set(p[i].v);
			if(x!=y)
			{
				union_set[y] = x;
				ans += p[i].len;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}