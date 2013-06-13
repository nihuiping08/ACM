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

const int MAXN = 305;
const ll INF = 1e16;
const int intINF = 1e9;

ll dp[MAXN][MAXN],c[MAXN][MAXN];
int n,m;

void cal(){
    /*
    说明：
    dp[i][j]表示前i位拥有j个被修补时的最小费用
    则dp[i+k][j+k] = min{ min{ dp[i][j]+c[i+1][i+k] },dp[i+k-1][j+k]}

    */
    dp[0][0] = 0;
    rep(i,n){
        dp[i][0] = 0;
        rep(j,i+1){
            if(dp[i][j]==INF)continue;
            dp[i+1][j] = min(dp[i+1][j],dp[i][j]);
            rep1(k,n-i)
                dp[i+k][j+k] = min(dp[i+k][j+k],dp[i][j]+c[i+1][i+k]);
        }
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int k;
    while(~RD3(n,m,k)){
        rep(i,n+1) rep(j,n+1)
            c[i][j] = dp[i][j] = INF;

        while(m--){
            int x,y,p;
            RD3(x,y,p);
            //cout<<x<<" "<<y<<" "<<p<<endl;
            REP(i,x,y)
                c[i][y] = min(c[i][y],ll(p));
        }
        /*
        puts("------------------");

        rep1(i,n)
            rep1(j,n)
                if(c[i][j]!=INF)
                    cout<<i<<" "<<j<<" "<<c[i][j]<<endl;;
        */

        cal();
        if(dp[n][k]==INF)
            puts("-1");
        else
            cout<<dp[n][k]<<endl;
    }

	return 0;
}
