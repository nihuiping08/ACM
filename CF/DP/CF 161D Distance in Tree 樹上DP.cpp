/*

題目：給出一棵樹，問路徑長為k的點對的數目
分析：樹上DP
    我們可以用size[x][dis]表示離節點x長度為dis的兒子個數
    所以我們可以再求size前相求添加該節點時所產生的新的路徑長度為k的點對
    數目。

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

#define lx(x) (x<<1)
#define rx(x) (x<<1|1)
#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

/******** program ********************/

const int MAXN = 50005;

ll dp[MAXN][502];
vector<int> vec[MAXN];
int n,m;
ll ans;

void dfs(int x,int fa){
    dp[x][0] = 1;
    foreach(i,vec[x]){
        int y = vec[x][i];
        if(y==fa)   continue;
        dfs(y,x);
        rep(j,m) // 表示向y節點分配j個，然後向x的其他兒子節點分配m-j-1個
            ans += dp[x][m-j-1]*dp[y][j];
        rep1(j,m) // 後面加上離y節點長度為j-1的兒子個數
            dp[x][j] += dp[y][j-1];
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD2(n,m)){
        rep1(i,n)
            vec[i].clear();
        memset(dp,0,sizeof(dp));
        int x,y;
        int tmp = n-1;
        rep(i,tmp){
            RD2(x,y);
            vec[x].pb(y);
            vec[y].pb(x);
        }

        ans = 0;
        dfs(1,0);

        cout<<ans<<endl;
    }

	return 0;
}
