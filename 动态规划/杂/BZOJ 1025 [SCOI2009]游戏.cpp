/*

題目：
    給出n，問排列n的循環節的個數
分析：
    按素數因子分類DP
    dp[i][j]表示前i個素數，組成的最小公倍數不大於j排列的個數
    則dp[i][j] = sigma( dp[i-1][j-p^k] )+dp[i-1][j]
    邊界為dp[i][0] = dp[0][i] = 1

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

const int MAXN = 1005;

ll dp[MAXN][MAXN];
int p[MAXN],top,n;
bool use[MAXN];

void init(){
    top = 0;
    for(int i=2;i<=n;i++)
        if(!use[i]){
            p[++top] = i;
            for(int j=i*2;j<=n;j+=i)
                use[j] = true;
        }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD(n)){
        init();

        memset(dp,0,sizeof(dp));
        rep(i,top+1)
            dp[i][0] = 1;
        rep(i,n+1)
            dp[0][i] = 1;

        rep1(i,top){
            for(int j=1;j<=n;j++){
                dp[i][j] += dp[i-1][j];
                for(int k=p[i];k<=j;k*=p[i])
                    dp[i][j] += dp[i-1][j-k];
            }
        }
        cout<<dp[top][n]<<endl;
    }

	return 0;
}
