/*

題目：
    給出a1<a2<...<an。問滿足：
    1.ai<ai_1
    2.gcd(ai,ai_1)>1
    的最長子序列

分析：
    按照每個輸入數據的素數因子進行DP。
    dp[ d[i] ] = max{ dp[ d[i] ] }+1

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

int dp[MAXN],n;
bool use[MAXN];
vector<int> p;

void init(){
    memset(use,false,sizeof(use));
    for(int i=2;i<MAXN;i++)
        if(!use[i]){
            p.pb(i);
            for(int j=i+i;j<MAXN;j+=i)
                use[j] = true;
        }
}

vector<int> cal(int n){
    vector<int> d;
    for(int i=0;p[i]*p[i]<=n;i++)
        if(n%p[i]==0){
            d.pb(p[i]);
            while(n%p[i]==0)
                n /= p[i];
        }
    if(n>1)
        d.pb(n);
    return d;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    init();
    while(~RD(n)){
        memset(dp,0,sizeof(dp));
        int ans = 0 , x;
        rep1(i,n){
            RD(x);
            vector<int> d = cal(x);
            int tmp = 0;
            foreach(j,d)
                tmp = max(tmp,dp[d[j]]);
            foreach(j,d)
                dp[d[j]] = tmp+1;
            ans = max(ans,tmp+1);
        }
        cout<<ans<<endl;
    }

	return 0;
}
