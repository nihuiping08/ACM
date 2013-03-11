/*

题目：
    求a^b所有约数的和

分析：
    积性函数
    预备知识：
    1.对a进行素数约数分解
    a = p1^k1 * p2^k2...pm^km
    2.a^b的所有约数之和
    sum = [ 1+p1+...+p1^k1 ]*...*[ 1+pm+pm^2+...+pm^km ]
    3.等比数列求和
    1+p+p^2+...+p^n
    递归二分然后快速幂取模

*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef __int64 ll;
typedef unsigned long long ull;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

#define MOD 9901

ll pw(ll p, ll n){
    ll sum = 1;
    while(n > 0){
        if(n & 1)
            sum = (sum * p) % MOD;
        n >>= 1;
        p = p * p % MOD;
    }
    return sum;
}

ll bin(ll p,ll n){
    if(n == 0) return 1;
    if(n & 1)
        return ((1+pw(p, n/2+1)) * bin(p, n/2)) % MOD;
    else
        return ((1+pw(p, n/2+1)) * bin(p, n/2-1) + pw(p, n/2)) % MOD;
}

void solve(ll a,ll b){
    int d[50];
    int num[50];
    int top = 0;
    memset(num,0,sizeof(num));

    for(ll i=2;i*i<=a;i++){
        if(a%i==0){
            d[++top] = i;
            while(a%i==0){
                num[top] ++;
                a /= i;
            }
        }
    }
    if(a>1){
        num[++top] = 1;
        d[top] = a;
    }
    ll ans = 1;
    rep1(i,top)
        ans = ans*bin(d[i],num[i]*b)%MOD;
    cout<<ans%MOD<<endl;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    ll a,b;
    while(cin>>a>>b)
        solve(a,b);

	return 0;
}
