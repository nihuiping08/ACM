/*

分析：與炮兵陣地基本一樣~~

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

const int MOD = 1e8;
const int MAXN = 600;

int dp[13][MAXN];
int sta[MAXN],sum[13],top;
int a[13],n,m;

bool ok(int x){
    return !(x&(x<<1));
}

void init(){
    int all = 1<<m;
    rep(i,all)
        if(ok(i))
            sta[top++] = i;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD2(n,m);
    int x;
    rep(i,n)
        rep(j,m){
            RD(x);
            if(x==0)
                a[i] |= 1<<j;
        }

    init();
    memset(dp,0,sizeof(dp));
    rep(i,top)
        if( !(sta[i]&a[0]) )
            dp[0][i] = 1;

    n --;
    rep1(x,n){
        rep(i,top){
            if(sta[i]&a[x])
                continue;
            rep(j,top){
                if(sta[i]&sta[j])
                    continue;
                dp[x][i] = (dp[x][i]+dp[x-1][j])%MOD;
            }
        }
    }

    int ans = 0;
    rep(i,top)
        ans = (ans+dp[n][i])%MOD;
    cout<<ans<<endl;

	return 0;
}
