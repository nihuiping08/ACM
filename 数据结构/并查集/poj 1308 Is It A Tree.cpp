/*
��Ŀ��
	���ܷ����һ����
������
	ע�⵽����Ϊ����������Ȳ��ܴ���һ��ͬʱ���нڵ㶼Ӧ����ָ�����
	�����ò��鼯�����Ƿ��й�ͬ�ĸ����еĻ��Ͳ������ˣ�ע���ʱӦ��
	Ҫ�ж��Ƿ���������ȣ��Ͳ�����ѹ��·���Ĳ��鼯������ֻ�ܰѳ���
	�ĵ㸶����ȵĵ�Ĳ��鼯����(��֪�����Լ�����Ƿ��д�����)��
	���Ҫ�ж��ǲ���ɭ�֣������õ�һ������������������еĽڵ��Ƿ�
	�н�����ֻҪ��һ��û�еĻ�������ɭ�ֶ�������
	������Ҳ������������

	��poj�е�discuss���ҵ�
	1: 0 0 ������һ����
	2: 1 1 0 0 ������ �����Լ�ָ���Լ�
	3: 1 2 1 2 0 0 ������....�Լ���ʼһֱ����ôWA  ������ �ظ�������ѽ~~5555
	4: 1 2 2 3 4 5 ������  ɭ�ֲ�������(��Ҫ��ע���Լ�)
	5: 1 2 2 3 3 4 4 5 5 6 6 7 7 8 8 9 9 1  ע�� һ���ڵ���ָ���Լ��ĸ��׻����� ���Ǵ���� �� 9-->1 ��
	6: 1 2 2 1 0 0 Ҳ�Ǵ����

*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 1000
//int Rank[X];
int set[X],p[X];
int u[1001],v[1001];
int find_set(int x)	//���鼯�Ĳ��Һ���
{
	/*if(x!=set[x])
		set[x] = find_set(set[x]);
	return set[x];*/
	if(x==set[x])
		return x;
	return find_set(set[x]);
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,m,cnt = 1;
	while(cin>>m>>n,m!=-1&&n!=-1)
	{
		if(!m&&!n)
		{	//�����Ļ���ֱ���������
			printf("Case %d is ",cnt++);
			printf("a tree.\n");
		}
		else
		{
			//memset(Rank,0,sizeof(Rank));
			for(int i=1;i<X;i++)
				set[i] = i;
			int count = 1;
			int flag = 0;
			u[count] = m;
			v[count++] = n;
			while(scanf("%d%d",&m,&n),m||n)
			{
				u[count] = m;
				v[count++] = n;
			}
			for(int i=1;i<count;i++)
			{	//�����Ƿ�������ͬ�ĸ�
				m = find_set(u[i]);
				n = find_set(v[i]);
				if(m==n||n!=v[i])//����ͬ�ĸ�������ȴ���1��������
				{
					flag = 1;
					break;
				}
				/*if(Rank[m]>Rank[n])
					set[n] = m;
				else
				{
					set[m] = n;
					if(Rank[m]==Rank[n])
						Rank[n]++;
				}*/
				set[n] = m;
			}
			if(!flag)
			{	//�����ɭ��ʱ��ͬ����������
				m = find_set(u[1]);
				for(int i=2;i<count;i++)
				{
					n = find_set(v[i]);
					if(m!=n)	//�������ڵ�û�й�ͬ�ĸ�����ɭ�ֲ�����
					{
						flag = 1;
						break;
					}
				}
			}
			printf("Case %d is ",cnt++);
			if(flag)
				printf("not ");
			printf("a tree.\n");
		}
	}
	return 0;
}