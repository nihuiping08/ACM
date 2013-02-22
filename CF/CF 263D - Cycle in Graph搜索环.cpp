/*
 * 题目：
 *		寻找图中长度至少为k+1的环
 *
 *	分析：
 *		其实可以直接爆搜可过。。
 *		另外，由于题目中保证了每个顶点都有至少k个相邻的顶点相连，所以我们可以从
 *		每个顶点出发，寻找一个度最小的相邻顶点，然后判断是否没被遍历，如果没有的话，
 *		可以直接从这个出发的点开始得到长度至少k+1的环。。。
 *	
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

const int X = 100005;

std::vector<int> vec[X];
int s[X];
int dfn[X];

int main(){
#ifndef ONLINE_JUDGE
	freopen("cf.txt","r",stdin);
#endif

	int n,m,k;
	while(~scanf("%d%d%d",&n,&m,&k)){
		int x,y;
		for(int i=1;i<=n;i++)
			vec[i].clear();
		while(m--){
			scanf("%d%d",&x,&y);
			vec[x].push_back(y);
			vec[y].push_back(x);
		}
		int top = 1;
		s[top] = 1;
		memset(dfn,0,sizeof(dfn));
		while(true){
			x = s[top];
			dfn[x] = top;
			int mind = n+1;
			int minp = -1;
			for(unsigned i=0;i<vec[x].size();i++){
				y = vec[x][i];
				if(dfn[y]<mind){
					mind = dfn[y];
					minp = y;
				}
			}
			if(mind==0)
				s[++top] = minp;
			else{
				printf("%d\n",top-mind+1);
				for(int i=mind;i<top;i++)
					printf("%d ",s[i]);
				printf("%d\n",s[top]);
				break;
			}
		}
	}

	return 0;
}
