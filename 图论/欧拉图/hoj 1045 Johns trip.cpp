/*

���⣺����JohnҪȥ������������,�������������n���ֵ�,ÿ���ֵ����Ľֵ�����������,����
������Щ�ֵ�����Ϣ(������x y z��ʾ�ֵ�z�������˵�Ϊx,y),�����Ƿ����ÿ���ֵ�ֻ����һ��,
�������,������ֵ�����С��·��,�����������"Round trip does not exist."���ֵ��� < 1995��
һ�������������44����·��·����ջ�����棬���ʱ��ջ����ʼ������ܱ�֤�ֵ�����С��������Ϊ
dfs��ʱ��·������ǽ����ģ����С��·����Ȼ�ȱ�������

�㷨��dfs

ע�⣺��ͼ��ʱ���¼���ǵ�ͱߵĹ�ϵ


���⣺�и�����������еĺ��ѣ������ظ���·���ֵ��б�ţ�������ʺ����кܶ���ѡ��Ļ���
ѡ������С���ߣ��ж��Ƿ����������·������������·����š�

���룺�ֵ��ͽ���ڵı�ţ�����ǵ�һ���ֵ��еĽ�С�㡣

����������·���·����ţ����û�������Ϣ��

˼·�������Ŀ������Ŀ�����Ǹ���ͨͼ�����Բ����ж��Ƿ���ͨ��Ȼ���ж�ŷ����·��֮�����
DFS��һ������·��������ջ�У�Ȼ�����ӡ���ɡ�


*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <stack>
using namespace std;
#define X 2000
int map[45][X],in[X],n,m,start;
bool visit[X];
stack<int> s;
bool is_euler()			//���еĶ��㶼ҪΪż����
{
	for(int i=1;i<=n;i++)
		if(in[i]%2)
			return false;
	return true;
}
void init()
{
	m = n = 0;
	memset(map,0,sizeof(map));
	memset(in,0,sizeof(in));
	memset(visit,false,sizeof(visit));
}
void add(int x,int y,int z)
{
	m++;
	n = max(n,z);
	map[x][z] = y;
	map[y][z] = x;
	in[x]++;
	in[y]++;
}
void dfs(int x)
{
	for(int i=1;i<=n;i++)
		if(map[x][i]&&!visit[i])
		{
			visit[i] = true;
			dfs(map[x][i]);
			s.push(i);
		}
}
void print()
{
	if(is_euler())
	{
		dfs(start);
		bool flag = false;
		while(s.size())
		{
			if(flag)
				printf(" ");
			printf("%d",s.top());
			flag = true;
			s.pop();
		}
	}
	else
		printf("Round trip does not exist.");
	printf("\n");
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int x,y,z;
	while(scanf("%d%d",&x,&y),x||y)
	{
		init();
		scanf("%d",&z);
		start = min(x,y);
		add(x,y,z);
		while(scanf("%d%d",&x,&y),x||y)
		{
			scanf("%d",&z);
			add(x,y,z);
		}
		print();
	}

	return 0;
}