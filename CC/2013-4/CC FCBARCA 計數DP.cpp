/*

題目：
    Ｍ和ｋ個人傳球，需要傳ｎ次球，並且球的傳出以及最後回到Ｍ手中。問
    方案數（不可以自己傳自己，但是可以傳給任意其他的人）。

分析：
    簡單的DP
    dp[i][j]表示第i個傳球傳給j人的方案個數。顯然遞推關係如下：
    dp[i][j] = sigma( dp[i-1][k] )-dp[i-1][j]

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
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

/******** program ********************/

const int MOD = 1e9+7;

ll dp[1002][12];
int n,m;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    while(ncase--){
        RD2(n,m);
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        rep1(i,n){
            ll sum = 0;
            for(int j=0;j<=m;j++)
                sum += dp[i-1][j];
            for(int j=0;j<=m;j++)
                dp[i][j] = (sum-dp[i-1][j])%MOD;
        }
        cout<<dp[n][0]<<endl;
    }

	return 0;
}
