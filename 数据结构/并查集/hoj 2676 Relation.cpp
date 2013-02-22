/*
��Ŀ��
	��ĳ��������Ա�����Ӵ�Ҫ�ж������Ƿ������ݣ�ȷʵ���ܲ����ף�
	���ڸ���ĳ�����ݹ�ϵͼ��������������������Ƿ�������ݹ�ϵ��
 
	�涨��x��y�����ݣ�y��z�����ݣ���ôx��zҲ�����ݡ����x,y�����ݣ�
	��ôx�����ݶ���y�����ݣ�y������Ҳ����x�����ݡ�
	Input
	����case��ÿ��case�У���һ������N(1 �� N �� 5000),M(1 �� M �� 5000),
	Q(1 �� Q �� 5000)���ֱ��ʾ��������ϵ����ѯ�ʴ�����
	��������M�У�ÿ����������a,b����ʾa��b֮�������ݹ�ϵ��
	��������Q�У�ÿ����������a,b����ʾѯ��a��b֮���Ƿ������ݹ�ϵ��
	ע���˵��±��1��ʼ��
	Output
	Ϊÿ��ѯ������һ�У��������ݹ�ϵʱ�����yes���������no.
	Sample Input
	5 2 3
	1 2
	2 3
	1 3
	2 4
	3 5 
	Sample Output
	yes
	no
	no

������
	���첢�鼯��ע�⵽���ݱȽϴ������������������scanf()��printf()������
	��Ȼ�ͻ�time limitted��������Ҫ�Ż��˵Ĳ��鼯��ѯ��������·��ѹ���ķ�����
	�������ҵ����Զ������ʱ��˳�㡱����������ֱ�����ӵ������档�����·��ѹ���ˡ�
	ʹ��·��ѹ���Ĵ������£�ʱ�临�ӶȻ���������Ϊ�ǳ����ġ�ʱ�临�Ӷ�O(n*��(n))
	���Ц�(x)������x=������ԭ����֮�ͣ���(x)������4��ʵ�ϣ�·��ѹ����Ĳ��鼯�ĸ�
	�Ӷ���һ����С�ĳ�����

	�ϲ�������
	C���Դ��룺 �ϲ�ʱ��Ԫ��������ȵ͵ļ��Ϻϲ���Ԫ�����������ļ��ϡ�
	void union_set(int x ,int y)
	{
	     fx = find_set(x);
	     fy = find_set(y);
	 
	     if (Rank[fx]>Rank[fy])
	        father[fy] = fx;
	     else
	     {
	        father[fx] = fy;
	        if(Rank[fx]==Rank[fy])
	           Rank[fx]++;
	     }
	}
	///////////��ʼ��
	void init(void)
	{
	    int i;
	    for (i=0; i<MAX; i++)
	        father[i] = i;
		memset(Rank,0,sizeof(Rank));
	}
	//////Ѱ�����������
	int find_set(int v)
	{
	    if (father[v] != v)
	        father[v] = find_set(father[v]);
	    return father[v];
	}
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 5010
int p[X],set[X];
int Rank[X];
int find_set(int x)
{	//�������������
	if(x!=set[x])
		set[x] = find_set(set[x]);
	return set[x];
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int n,m,q,a,b;
	while(cin>>n>>m>>q)
	{
		for(int i=0;i<=n;i++)
			set[i] = i;
		memset(Rank,0,sizeof(Rank));
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&a,&b);
			///////////ѹ��·��
			int fx = find_set(a);
			int fy = find_set(b);
			if(Rank[fx]>Rank[fy])
				set[fy] = fx;
			else
			{
				set[fx] = fy;
				if(Rank[fx]==Rank[fy])
					Rank[fy]++;
			}
		}
		for(int i=1;i<=q;i++)
		{
			scanf("%d%d",&a,&b);
			int x = find_set(a);
			int y = find_set(b);
			if(x!=y)
				printf("no\n");
			else
				printf("yes\n");
		}
	}
	return 0;
}


