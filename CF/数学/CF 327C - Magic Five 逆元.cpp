#include <set>
#include <map>
#include <list>
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
#define All(vec) vec.begin(),vec.end()
#define MP make_pair
#define PII pair<int,int>
#define PQ priority_queue

/******** program ********************/

const ll MOD = 1000000007;

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

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    string s;
    ll n;
    while(cin>>s>>n){
        ll len = s.size();
        ll ans = 0;

        rep(i,len)
            if(s[i]=='0'||s[i]=='5')
                ans += pw(2,i)*Inv( pw(2,len)-1 )%MOD*( pw(2,len*n)-1 )%MOD;

        cout<<(ans%MOD+MOD)%MOD<<endl;
    }

	return 0;
}
