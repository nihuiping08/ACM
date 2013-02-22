#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define X 110
int pa[X],r[X],n,m;
bool use[X*X];
struct node
{
	int x,y,w;
}p[X*X];
bool cmp(node a,node b)
{
	return a.w<b.w;
}
int find_set(int x)
{
	if(x!=pa[x])
		pa[x] = find_set(pa[x]);
	return pa[x];
}
void union_set(int x,int y)
{
	pa[x] = y;
}
void make_set()
{
	for(int i=1;i<=n;i++)
		pa[i] = i;
}
int kruskal()
{
	memset(use,false,sizeof(use));
	int px,py,cnt = 0,ans = 0;
	make_set();
	sort(p,p+m,cmp);
	for(int i=0;i<m;i++)
	{
		px = find_set(p[i].x);
		py = find_set(p[i].y);
		if(px!=py)
		{
			use[i] = true;
			cnt++;
			ans += p[i].w;
			union_set(px,py);
			if(cnt==n-1)
				return ans;
		}
	}
	return ans;
}
int sec_kruskal()
{
	int cnt,res,ans = 1<<30;
	for(int i=0;i<m;i++)
	{
		if(use[i])
		{
			make_set();
			cnt = res = 0;
			for(int j=0;j<m;j++)
			{
				if(i!=j)
				{
					int px = find_set(p[j].x);
					int py = find_set(p[j].y);
					if(px!=py)
					{
						union_set(px,py);
						res += p[j].w;
						cnt++;
						if(cnt==n-1)
						{
							ans = min(ans,res);
							break;
						}
					}
				}
			}
		}
	}
	return ans;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=0;i<m;i++)
			scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].w);
		int ans = kruskal();
		int ans2 = sec_kruskal();
		if(ans==ans2)
			printf("Not Unique!\n");
		else
			printf("%d\n",ans);
	}
	return 0;
}