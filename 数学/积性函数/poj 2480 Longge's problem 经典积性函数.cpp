/*

题目：求sigma( gcd(i,n) )
分析：gcd(i,n) = gcd(i,a*b) = gcd(i,a)*gcd(i,b)
    所以gcd是一个积性函数。
    积性函数的和还是积性函数。
    所以
    f(n) = sigma( gcd(i,n) )也是积性函数
	f(n) = f(p1^k1 * ... * pm^km) = f(p1^k1) * f(p2^k2) *...* f(pm^km)
    又因为
	f(n) = sigma( d* phi(n/d) ),i = d|n
    所以可以化为
    f(p^k) = sigma( p^i * phi( p^(k-i) ) )
    而
    phi(p^k) = p^k-p^(k-1)
    所以问题得以解决

*/
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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 50000;

vector<ull> prime;
bool use[MAXN];
ull n;

void init(){
    memset(use,false,sizeof(use));
    for(int i=2;i<MAXN;i++)
        if(use[i]==false){
            prime.pb(i);
            for(int j=i+i;j<MAXN;j+=i)
                use[j] = true;
        }
}

ull pw(ull p,int k){
    if(k==0)    return 1;
    ull ans = p-1;

    while(--k)
        ans *= p;
    return ans;
}

ull fpk(ull p,int k){
    ull ans = 0;
    ull t = 1;
    for(int i=0;i<=k;i++){
        ans += t*pw(p,k-i);
        t *= p;
    }
    return ans;
}

void solve(){
    ull ans = 1;
    for(int i=0;prime[i]*prime[i]<=n;i++){
        ull p = prime[i];
        if(n%p)
            continue;
        int k = 0;
        while(n%p==0){
            n /= p;
            k ++;
        }
        ans *= fpk(p,k);
    }
    if(n>1)
        ans *= fpk(n,1);
    cout<<ans<<endl;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    init();
    while(cin>>n)
        solve();

	return 0;
}

