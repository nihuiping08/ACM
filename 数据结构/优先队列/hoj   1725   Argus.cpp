/*

��Ŀ������,����ID Ƶ�ʣ�����ѯ�ʴ���K������ǰK������ID�Ƕ��١�
��ѧ�����ȶ��е���һ��д����֮ǰѧ����priority_queue<int ,vector<int>,greater<int> > q
������ʽ

*/
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
char in[10];
struct node
{
	int id,num,st;
	friend bool operator <(struct node a,struct node b)
	{
		if(a.num==b.num)
			return a.id>b.id;
		return a.num>b.num;
	}
};
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	priority_queue<node> q;
	node p;
	int id,num;
	while(scanf("%s",in),in[0]!='#')
	{
		scanf("%d%d",&id,&num);
		p.id = id;
		p.num = num;
		p.st = num;
		q.push(p);
	}
	scanf("%d",&num);
	while(num--)
	{
		p = q.top();
		q.pop();
		printf("%d\n",p.id);
		p.num += p.st;
		q.push(p);
	}
	return 0;
}