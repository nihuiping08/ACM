/*

题目：
    称一个1,2,...,N的排列P1,P2...,Pn是Magic的，当且仅当2<=i<=N时，Pi>Pi/2. 计算1，2，...N的排列中
	有多少是Magic的，答案可能很大，只能输出模P以后的值

分析：
	我们可以把n个数扔到一个堆里面，由于堆是一棵完全二叉树，所以我们假设左儿子的节点数为L，右儿子数为
	R时，显然节点总数为n = L+R+1，所以我们可以用dp[n]表示问题的解，显然转移方程为
	dp[n] = dp[L]*dp[R]*C(n-1,L).
	由于n比较大，所以我们需要用ex_gcd求逆元。
	
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

const int MAXN = 1e6+5;

ll fac[MAXN],dp[MAXN];
int n,MOD;

void init(){
    fac[0] = 1;
    rep1(i,n)
        fac[i] = fac[i-1]*i%MOD;
}

void ex_gcd(ll a,ll b,ll &gcd,ll &x,ll &y){
    if(b==0){
        x = 1;
        y = 0;
        gcd = a;
    }else{
        ex_gcd(b,a%b,gcd,y,x);
        y -= x*(a/b);
    }
}

ll Inv(ll n){
    ll x,y,gcd;
    ex_gcd(n,MOD,gcd,x,y);
    return gcd==1 ? (x%MOD+MOD)%MOD : -1;
}

ll C(int a,int b){
    return fac[a] * Inv( fac[b]*fac[a-b]%MOD ) % MOD;
}

int bit(int n){
    int ans = 0;
    while(n){
        ans += n&1;
        n >>= 1;
    }
    return ans;
}

void solve(){
    dp[0] = dp[1] = 1;
    int l = 0 , r = 0;
    int tmp = 0;
    REP(i,2,n){
        if(bit(i)==1)
            tmp += tmp+1;
        if(l<tmp)   l ++;
        else        r ++;
        dp[i] = dp[l]*dp[i-l-1]%MOD*C(i-1,l)%MOD;
    }
    cout<<dp[n]<<endl;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    cin>>n>>MOD;
    init();
    solve();

	return 0;
}
