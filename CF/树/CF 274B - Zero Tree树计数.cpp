#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)

const int MAXN = 1e5+5;

vector<int> vec[MAXN];

int val[MAXN],n;
ll dp[MAXN][2];

void dfs(int x,int fa){
	//cout<<x<<" "<<fa<<endl;
	foreach(i,vec[x]){
		int y = vec[x][i];
		if(y==fa)
			continue;
		dfs(y,x);
		dp[x][0] = max(dp[x][0],dp[y][0]); // add
		dp[x][1] = max(dp[x][1],dp[y][1]); // sub
	}
	val[x] += dp[x][0]-dp[x][1];
	if(val[x]<0)
		dp[x][0] -= val[x];
	if(val[x]>0)
		dp[x][1] += val[x];
	//cout<<x<<" "<<dp[x][0]<<" "<<dp[x][1]<<endl;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
#endif

	int x,y;
	while(cin>>n){
		rep(i,n+1)
			vec[i].clear();
		rep(i,n-1){
			scanf("%d%d",&x,&y);
			vec[x].push_back(y);
			vec[y].push_back(x);
		}
		REP(i,1,n+1)
			scanf("%d",&val[i]);
		memset(dp,0,sizeof(dp));
		dfs(1,-1);
		cout<<dp[1][0]+dp[1][1]<<endl;
	}

	return 0;
}
