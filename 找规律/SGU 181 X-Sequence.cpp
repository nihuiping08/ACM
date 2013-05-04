/*

題目：f[n] = ( a*f[n-1]^2 + b*f[n-1] + c )%MOD，求f[k]
分析：找循環節。

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

const int MAXN = 10005;

int dp[MAXN],ans[MAXN];
int x,a,b,c,MOD,n;

int cc(int x){
    return (x*x%MOD*a%MOD+x*b+c)%MOD;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD4(x,a,b,c);
    RD2(MOD,n);

    if(n==0){
        cout<<x<<endl;
        return 0;
    }

    memset(dp,-1,sizeof(dp));
    int top = 0;
    ans[top++] = x%MOD;

    int now = 0;
    dp[ now = x%MOD ] = 0;
    now = cc(now);
    while(dp[now]==-1){
        ans[top] = now;
        dp[now] = top;
        now = cc(now);
        top ++;
    }

    //rep(i,top)
    //    cout<<ans[i]<<" ";
    //cout<<endl;

    if(n<top)
        cout<<ans[n]<<endl;
    else{
        //debug;
        //cout<<top<<" "<<dp[now]<<endl;
        cout<<( ans[ (n-dp[now])%(top-dp[now])+dp[now] ] )<<endl;
    }

    return 0;
}
