/*

題目：
    給出a,b數組，現在只允許兩個不同的數配對，是的配對數的差值的絕對值
    最小化。問最小的配對數
分析：
    對a,b排序，然後決策只會與前三個數有關。

*/
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

const int MAXN = 1e5+5;
const ll INF = 1e13;

ll dp[MAXN];
int a[MAXN],b[MAXN];

ll P(ll x,ll y){
    return x==y?INF:max(x-y,y-x);
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int n;
    while(~RD(n)){

        rep1(i,n)
            RD2(a[i],b[i]);

        sort(a+1,a+n+1);
        sort(b+1,b+n+1);

        dp[0] = 0;
        dp[1]=P(a[1],b[1]);
        dp[2] = min(dp[1]+P(a[2],b[2]),P(a[1],b[2])+P(a[2],b[1]));

        REP(i,3,n){
            ll a0 = P(a[i],b[i])+dp[i-1];
            ll a1 = P(a[i-1],b[i])+P(a[i],b[i-1])+dp[i-2];

            ll a2 = P(a[i-2],b[i-1])+P(a[i-1],b[i])+P(a[i],b[i-2]);
            ll a3 = P(b[i-2],a[i-1])+P(b[i-1],a[i])+P(b[i],a[i-2]);
            ll a4 = P(a[i-2],b[i])+P(a[i-1],b[i-1])+P(a[i],b[i-2]);
            ll tmp = min(a2,min(a3,a4))+dp[i-3];

            dp[i] = min( min(a0,a1) , tmp );
        }

        if(dp[n]>=INF)
            puts("-1");
        else
            cout<<dp[n]<<endl;
    }

    return 0;
}
