/*

分析：
    可以推出递推式：a_i = (2*a_i_1)%(n+1)
    进而推出 a_m = a_0*2^m%(n+1)
    a_m = l。
    根据同余方程 ax == c%b
    用扩展欧几里得算出。
    注意到数据范围为 10^10，两者相乘会爆long long，需要用到类似于快速幂
    的方式计算出两个数的乘积

*/
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

ll MOD;

ll cc(ll x,ll y){
    ll sum = 0;
    while(y>0){
        if(y&1)
            sum = (sum+x)%MOD;
        y >>= 1;
        x = (x<<1)%MOD;
    }
    return sum;
}

ll pw(ll p,ll exp){
    ll ans = 1;
    while(exp>0){
        if(exp&1)
            ans = cc(ans,p);
        exp >>= 1;
        p = cc(p,p);
    }
    return ans;
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

void solve(ll a,ll b,ll c){
	ll x,y,gcd;
    ex_gcd( a,b,gcd,x,y );
    if(c%gcd)   return;

    c /= gcd;
    x = cc(x,c);
    if(x<0)
        x = x+10000*MOD;
    cout<<x%MOD<<endl;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    ll n,m,l;
    while(cin>>n>>m>>l){
        MOD = n+1;
        solve( pw(2,m),MOD,l );
    }

	return 0;
}
