/*

��Ŀ��
	�������Ƴ��µ�������䷽���������˶�A B������ͬ�𰸵��˿��Է���A�����ᣬ
	��C D������ͬ�𰸵��˿��Է���B�����ᣬÿһ�����������û�����ƵĻ����ʿ�
	������Ҫ������ټ�������ֺܷ�����ѧ��

������
	ÿһ��ѧ�������Է�����A������i������B������j����ˣ�g[i][j] = true���ɴ˿���
	����һ������ͼ����hungry�㷨��
	������������ݱȽϴ���������ѭ���жϵĻ����ᳬʱ�����Կ���������Ȼ�����ж�
	��ǰ���һ��һ������һ������g[i][j] = true,i �� j��ֵ��Ҫ�ȴ���ã����忴����

*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define X 102
int ym[X],na,nb;
bool g[X][X],use[X];
struct node
{
	int a,b,c,d;
	int na,nb;			//���ڵ�����A B�ķ����
}p[X*X];
bool cmp1(node a,node b)//��ǰ�����ؼ�������
{
	if(a.a==b.a)
		return a.b<b.b;
	else
		return a.a<b.a;
}
bool cmp2(node a,node b)//�Ժ������ؼ��ֽ�������
{
	if(a.c==b.c)
		return a.d<b.d;
	else
		return a.c<b.c;
}
bool dfs(int u)	//Ѱ��һ������·
{
	int t;
	for(int v=1;v<=nb;v++)
		if(g[u][v]&&!use[v])
		{
			use[v] = true;
			t = ym[v];
			ym[v] = u;	//·��ȡ������
			if(t==-1||dfs(t))//Ѱ���Ƿ�Ϊ�����
				return true;
			ym[v] = t;
		}
		return false;
}
int hungry()	//
{
	memset(ym,-1,sizeof(ym));
	int ret = 0;			//��ʼʱ�����Ϊ��
	for(int u=1;u<=na;u++)	//�Ӷ���ͼ���󲿵�ÿ�����㿪ʼѰ�������
	{
		memset(use,false,sizeof(use));
		if(dfs(u))			//���ҵ�������ȡ������ƥ���һ
			ret++;
	}
	return ret;				//�������ƥ����
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++)
			scanf("%d%d%d%d",&p[i].a,&p[i].b,&p[i].c,&p[i].d);
		sort(p,p+n,cmp1);
		na = nb = 1;
		p[0].na = p[0].nb = 1;
		int ta = p[0].a,tb = p[0].b;
		for(int i=1;i<n;i++)		//��A��������б��
		{
			if(p[i].a==ta&&p[i].b==tb)	//�����ǰ���һ���Ļ�����A�������λ���뵱ǰ��B����������һ��
				p[i].na = na;
			else						//����B������������һ
			{
				p[i].na = ++na;
				ta = p[i].a;			//����
				tb = p[i].b;
			}
		}
		memset(g,false,sizeof(g));

		sort(p,p+n,cmp2);	//�Ժ������ؼ��ֽ�������
		int tc = p[0].c,td = p[0].d;
		for(int i=0;i<n;i++)
		{
			if(p[i].c==tc&&p[i].d==td)	//�����ǰ���һ���Ļ�����B�������λ���뵱ǰ��B����������һ��
				p[i].nb = nb;
			else						//����B������������һ
			{
				p[i].nb = ++nb;
				tc = p[i].c;			//����
				td = p[i].d;
			}
			g[p[i].na][p[i].nb] = true;//�൱��A������i��B������j����
		}
		printf("%d\n",hungry());
	}

	return 0;
}