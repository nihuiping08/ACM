/*

分析：
    背包問題的另一種寫法。如果對於每個詢問都進行一次多重背包會TLE。
    假設dp[i]表示四種硬幣不受限制的情況下的方案數，則方程如下：
    dp[i] = sigma(dp[i-c[j]]),c[j]<=i
    爲了避免重複計算，我們需要以j作為階段劃分。
    對於每個問題，我們可以先算出價值為sum的方案數，然後-第一種硬幣超過
    限制的數-第二種硬幣超過限制的數-第三種硬幣超過限制的數-第四種硬幣
    超過限制的數+第一第二種超過限制的數....

    很顯然，價值為sum的方案數為 dp[sum]
    以下若下標為負數，方案數為0
    第i種硬幣超過限制的數為 dp[sum-ci*(di+1)]
    第i第j種超過限制的數為 dp[sum-ci*(di+1)-cj*(dj+1)]

    所以我們可以用容斥原理進行求解。

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

const int MAXN = 100005;

ll dp[MAXN+1];
int a[5],c[5],sum,tot;

ll cc(int x){
    return x>=0 ? dp[x] : 0;
}

ll rc(){
    ll ans = 0;
    rep(i,16){
        ll tmp = 0;
        int ok = 0;
        rep(j,4)
            if(i&(1<<j)){
                ok ^= 1;
                tmp += ll(a[j]+1)*c[j];
            }
        tmp = cc(sum-tmp);
        if(ok)
            ans += tmp;
        else
            ans -= tmp;
    }
    return -ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    rep(i,4)
        RD(c[i]);
    RD(tot);

    dp[0] = 1;
    rep(j,4)
        rep1(i,MAXN)
            if(i>=c[j])
                dp[i] += dp[i-c[j]];

    while(tot--){
        rep(i,4)
            RD(a[i]);
        RD(sum);
        cout<<rc()<<endl;
    }

	return 0;
}
