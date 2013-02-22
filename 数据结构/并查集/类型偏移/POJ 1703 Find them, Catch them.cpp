/*

��Ŀ��
	ĳ��������ڰ���ڸ���ĳ���˲�����ͬһ��������ĳ�����ǲ���ͬ��һ���ڰ

������
	�������ƫ�ƺͲ��鼯��������0��ʾA�1��ʾB�������Rank[i]

*/
/*
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 100005
int pa[X],Rank[X],n,m,cnt;
int find_set(int x)
{
	if(x==pa[x])
		return x;
	int t = pa[x];
	pa[x] = find_set(t);
	Rank[x] = (Rank[x]+Rank[t])%2;
	return pa[x];
}
void union_set(int x,int y)
{
	int px = find_set(x);
	int py = find_set(y);
	pa[py] = pa[px];
	Rank[py] = (Rank[x]+1-Rank[y]+2)%2;
}
void print(int x,int y)
{
	int px,py;
	px = find_set(x);
	py = find_set(y);
	if(px==py)
	{
		if(Rank[x]==Rank[y])
			printf("In the same gang.\n");
		else
			printf("In different gangs.\n");
	}
	else
		printf("Not sure yet.\n");
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t,x,y;
	char ch[2];
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			pa[i] = i;
			Rank[i] = 0;
		}
		cnt = 100001;
		while(m--)
		{
			scanf("%s%d%d",ch,&x,&y);
			if(ch[0]=='A')
				print(x,y);
			else
				union_set(x,y);
		}
	}
	return 0;
}
*/

/*

��������
	���԰���������һ��ʹ��s[x]��s[x+n]Ϊ�жԹ�ϵ���ϲ�ʱ��������Ϊ�жԹ�ϵʱ��
	ֻ��ֱ�ϲ�����������a,b��a��b+n��b��a+n���ɣ����ַ���Ӧ���ǱȽϺ����ġ�
	�����ľ��Ǹ����鼯����������м���

*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define X 200005
int pa[X],n,m;
int fs(int x)
{
	if(x!=pa[x])
		pa[x] = fs(pa[x]);
	return pa[x];
}
void us(int i,int j)
{
	i = fs(i);
	j = fs(j);
	if(i!=j)
		pa[i] = j;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t,x,y;
	char ch[2];
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=2*n;i++)
			pa[i] = i;
		while(m--)
		{
			scanf("%s%d%d",ch,&x,&y);
			if(ch[0]=='A')
			{
				if(fs(x)==fs(y))
					printf("In the same gang.\n");
				else if(fs(x)==fs(y+n)||fs(y)==fs(x+n))
					printf("In different gangs.\n");
				else
					printf("Not sure yet.\n");
			}
			else
			{
				us(x,y+n);		//�жԹ�ϵ
				us(y,x+n);
			}
		}
	}
	return 0;
}