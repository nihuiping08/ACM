/*
 * 题目：
 *		n个人围成一个圈，现在开始数数，比如5个人的时候，标号从1到5逆时针开始，数数的人
 *		的标号依次为1-2,2-3,3-4,4-5,5-1,1-3,2-4,3-5,4-1,5-2。现在给出2*n个关系，问是否
 *		能够确定人的座位顺序
 *
 * 分析：
 *		dfs加枚举，我们画个图可以发现，当答案中相邻的三项为a,b,c时，肯定有边a-b,b-c,a-c
 *		所以我们可以从1开始出发，搜索他相邻的四个点，若存在边a-b,b-c,a-c，肯定可以从a出发
 *		到达b，再由b出发到达其他的点最后才回到c。所以可以直接dfs搜索
 *
 * */
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

#define debug puts("here");

const int X = 200005;

int ans[X],n;
bool use[X];
vector<int> vec[X];

bool dfs(int pre,int now,int len,int start){
	ans[len] = now;
	use[now] = true;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++){
			int x = vec[pre][i];
			int y = vec[now][j];
			if(x!=y)
				continue;
			if(len==n-1 && x==start)
				return start == x;
			if( !use[x] )
				return dfs(now,x,len+1,start);
		}
	return false;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("cf.txt","r",stdin);
#endif

	while(~scanf("%d",&n)){
		int x,y;
		int m = n<<1;
		for(int i=1;i<=n;i++)
			vec[i].clear();
		while(m--){
			scanf("%d%d",&x,&y);
			vec[x].push_back(y);
			vec[y].push_back(x);
		}
		bool ok = true;
		for(int i=1;i<=n;i++){
			if(vec[i].size()!=4){
				puts("-1");
				ok = false;
				break;
			}
		}
		if(!ok)
			continue;
		for(int i=0;i<4&&ok;i++)
			for(int j=i+1;j<4;j++){
				int x = vec[1][i];
				int y = vec[1][j];
				ans[1] = 1;
				ans[n] = y;
				memset(use,false,sizeof(use));
				use[1] = true;
				use[x] = use[y] = true;
				if(dfs(1,x,2,y)){
					for(int k=1;k<n;k++)
						printf("%d ",ans[k]);
					printf("%d\n",ans[n]);
					ok = false;
					break;
				}
			}
		if(ok)
			puts("-1");
	}
	return 0;
}

