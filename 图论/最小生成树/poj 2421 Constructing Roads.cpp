/*
���⣺
	��n����ׯ����·�������Ѿ�����һЩ·������С����
������
	��С��������������kruskal�㷨���ģ����Ѿ��޺õ�·�ò��鼯����������
	�����ľ͸�kruskal�㷨һ���ˡ�����Խ�����⵽���ڻ�û��ȫȥ�����㵽
	run time error��3�Σ�������ѹ��·���������ֱȲ��ö���14ms����������
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;
#define X 15000
int set[X];
int Rank[X];
typedef struct node
{	//����ṹ�崢��ߺ�������
	int u,v,len;
}node;
struct node p[X];
int cmp(const void *a,const void *b)
{	//���ǽ�������
	struct node *c = (struct node *)a;
	struct node *d = (struct node *)b;
	return c->len-d->len;
}
int find_set(int x)
{	//���鼯���Һ���
	/*
	if(x==set[x])�����ǵ���û��ѹ��·��������
		return x;
	return find_set(set[x]);
	*/
	if(x!=set[x])
		set[x] = find_set(set[x]);
	return set[x];
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,q,a,b;
	while(cin>>n)
	{
		p[0].len = p[0].u = p[0].v = -1;//��Ϊ�������Ǵ�p[0]��ʼ��
		int cnt = 1;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				p[cnt].u = i;
				p[cnt].v = j;
				scanf("%d",&p[cnt++].len);
			}
		}
		memset(Rank,0,sizeof(Rank));
		qsort(p,cnt,sizeof(p[0]),cmp);
		for(int i=1;i<=cnt;i++)
			set[i] = i;
		cin>>q;
		for(int i=1;i<=q;i++)
		{		//�����еĵ�·�ò��鼯��ʽ��������
			scanf("%d%d",&a,&b);
			int fu = find_set(a);
			int fv = find_set(b);
			/*if(fu!=fv)
				set[fu] = fv;*/
			if(Rank[fu]>Rank[fv])
				set[fv] = fu;
			else
			{
				set[fu] = fv;
				if(Rank[fu]==Rank[fv])
					Rank[fv]++;
			}
		}
		int ans = 0;
		for(int i=1;i<cnt;i++)
		{	//�������еıߣ����Ƿ��Ѿ���������
			int fu = find_set(p[i].u);
			int fv = find_set(p[i].v);
			if(fu!=fv)
			{
				ans+=p[i].len;
				//set[fv] = fu;
			}
			if(Rank[fu]>Rank[fv])
				set[fv] = fu;
			else
			{
				set[fu] = fv;
				if(Rank[fu]==Rank[fv])
					Rank[fv]++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}