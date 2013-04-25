/*

題目：
    每個球有價值以及顏色，現在任意選擇一些球出來，並且球的順序
跟原來的一樣，如果選出的球跟前一個球同色，得到的值 += a*val_i，
否則得到的值 += b*val_i。問如何得到最大的值。

分析：
    DP
    由於最大價值可能跟前者同色，或者不同色，所以我們需要記錄最大
    值以及次大值，保證這兩個值不同色，所以我們在DP轉移的時候能夠
    保證必定在這兩個值中轉換過來。

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

const int MAXN = 1e5+5;
const ll INF = 1e18;

int val[MAXN],c[MAXN],n,m;
ll dp[MAXN];

void solve(){
    fill(dp+1,dp+n+1,-INF);
    ll x,y;
    scanf("%I64d%I64d",&x,&y);

    int id1 = 0 , id2 = 0;
    rep1(i,n){
        dp[c[i]] = max( dp[c[i]],max(dp[c[i]]+x*val[i] , y*val[i]) );
        if(id1==c[i])
            dp[c[i]] = max(dp[c[i]],dp[id2]+y*val[i]);
        else
            dp[c[i]] = max(dp[c[i]],dp[id1]+y*val[i]);
        if(dp[c[i]]>dp[id1]){
            if(id1!=c[i]){
                id2 = id1;
                id1 = c[i];
            }
        }else if(dp[c[i]]>dp[id2]&&id1!=c[i])
            id2 = c[i];
    }

    ll ans = 0;
    ans = max(ans,*max_element(dp+1,dp+n+1));
    cout<<ans<<endl;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m){
        rep1(i,n)
            scanf("%d",&val[i]);
        rep1(i,n)
            scanf("%d",&c[i]);
        while(m--)
            solve();
    }

	return 0;
}
