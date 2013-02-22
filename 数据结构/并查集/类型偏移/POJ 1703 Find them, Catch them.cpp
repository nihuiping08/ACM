/*

题目：
	某市有两伙黑帮，现在给出某两人不属于同一势力，问某两人是不是同属一个黑帮。

分析：
	利用类别偏移和并查集做，其中0表示A伙，1表示B伙，当数组Rank[i]

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

方法二：
	可以把数组扩大一倍使得s[x]与s[x+n]为敌对关系，合并时即给出互为敌对关系时，
	只需分别合并（假设输入a,b）a与b+n，b与a+n即可，这种方法应该是比较好理解的。
	其他的就是跟并查集基本步骤进行即可

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
				us(x,y+n);		//敌对关系
				us(y,x+n);
			}
		}
	}
	return 0;
}