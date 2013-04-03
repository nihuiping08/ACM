/*

題目：
    維護DP
    sum[i]表示sigma(a[j]),0<j<=i
    dp[i] = max{ dp[j]+a*(sum[i]-sum[j])^2 + b*(sum[i]-sum[j]) + c }

分析：
    單調隊列優化DP
    我們可以假設有兩個決策點k>j，並且k比j更優
    有
    dp[k]+a*(sum[i]-sum[k])^2 + b*(sum[i]-sum[k]) + c >
    dp[j]+a*(sum[i]-sum[j])^2 + b*(sum[i]-sum[j]) + c
    可以化簡為
    dp[k]+a*sum[k]*sum[k]-b*sum[k]-(dp[j]+a*sum[j]*sum[j]-b*sum[j])
        >2*a*sum[i]*(sum[k]-sum[j])
    所以我們維護一下單調隊列即可。
    需要注意一下a的符號，所以我們最好不用考慮a符號

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

const int MAXN = 1e6+5;

ll sum[MAXN],a,b,c;
ll dp[MAXN];
ll g[MAXN];
int q[MAXN],n;

ll G(int k,int j){
    return g[k]-g[j];
}

ll S(int k,int j){
    return (sum[k]-sum[j])*a*2;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    RD(n);
    cin>>a>>b>>c;

    dp[0] = 0;
    int x;
    rep1(i,n){
        RD(x);
        sum[i] = sum[i-1]+x;
    }

    int H = 0,T = 0;
    q[T] = 0;

    rep1(i,n){
        /// 維護隊列單調遞減
        while(H<T && G(q[H+1],q[H])>=sum[i]*S(q[H+1],q[H]))
            H ++;
        int j = q[H];
        ll x = sum[i]-sum[j];
        dp[i] = dp[j]+a*x*x+b*x+c;
        g[i] = dp[i]+a*sum[i]*sum[i]-b*sum[i];
        /// 由於a<0，所以需要改變符號
        while(H<T && G(q[T],q[T-1])*S(i,q[T])>=G(i,q[T])*S(q[T],q[T-1]))
            T --;
        q[++T] = i;
    }

    cout<<dp[n]<<endl;

    return 0;
}
