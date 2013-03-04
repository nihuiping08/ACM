/*

题目：
    给出一棵树，选择一颗子树，使得子树的权值最大

分析：
    简单树形DP。

*/
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
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 16005;

vector<int> vec[MAXN];
int val[MAXN],dp[MAXN],n;

void dfs(int x,int fa){
    dp[x] = val[x];
    foreach(i,vec[x]){
        int y = vec[x][i];
        if(y==fa)
            continue;
        dfs(y,x);
        dp[x] += max(dp[y],0);
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD(n);
    rep(i,n)
        RD(val[i+1]);
    int x,y;
    rep(i,n-1){
        RD2(x,y);
        vec[x].pb(y);
        vec[y].pb(x);
    }
    dfs(1,0);
    int ans = -1e9;
    rep(i,n)
        ans = max(ans,dp[i+1]);
    cout<<ans<<endl;

	return 0;
}
