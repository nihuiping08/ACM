/*

题目：
	就是2318题的变形
	
分析：
	需要对输入的划分线先排序，然后再用二分+叉积，二分找出线段的
	位置

*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define X 1005
struct node
{
	int top,buttom;
	friend bool operator < (node a,node b)
	{
		return a.buttom<b.buttom;
	}
}p[X];
int num[X],ans[X],n,m,X0,Y0,X1,Y1;
long long det(int x1,int y1,int x2,int y2)//叉积
{
	return (long long)x1*y2-(long long)x2*y1;
}
void binary_search(int x,int y)
{
	int up = n+1,down = 0;
	while(true)		//二分搜索出线段的位置
	{
		int mid = (up-down)/2+down;
		if(mid==down)
			break;
		if(det(p[mid].top-p[mid].buttom,Y0-Y1,x-p[mid].buttom,y-Y1)<0)//点在线段的右面
			down = mid;
		else
			up = mid;
	}
	num[down]++;
}
int main()
{
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	int x,y;
	while(cin>>n,n)
	{
		memset(num,0,sizeof(num));
		cin>>m>>X0>>Y0>>X1>>Y1;
		for(int i=1;i<=n;i++)
			cin>>p[i].top>>p[i].buttom;
		sort(p+1,p+n+1);	//对输入的点排序
		while(m--)
		{
			cin>>x>>y;
			binary_search(x,y);
		}
		memset(ans,0,sizeof(ans));
		int MAX = -1;
		for(int i=0;i<=n;i++)
		{
			MAX = max(MAX,num[i]);//整个区间最多球的个数
			ans[num[i]]++;		//将结果保存到数组ans中，ans的下标即为数目，ans[]为答案
		}
		cout<<"Box"<<endl;
		for(int i=1;i<=MAX;i++)
			if(ans[i])
				printf("%d: %d\n",i,ans[i]);
	}

	return 0;
}