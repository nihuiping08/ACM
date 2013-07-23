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
#define cmax(x,y) x = max(x,y)
#define cmin(x,y) x = min(x,y)

/******** program ********************/

const ll MOD = 1e9+7;

ll pw(ll n,int exp){
    ll ans = 1;
    while(exp>0){
        if(exp&1)
            ans = ans*n%MOD;
        n = n*n%MOD;
        exp >>= 1;
    }
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    while(ncase--){
        int n,k;
        RD2(n,k);

        if(k>n)
            puts("0");
        else if(k==n)
            puts("1");
        else{
            if(n==1)
                puts("1");
            else if(n==2)
                puts("2");
            else{
                ll ans = (n-k-1)*pw(2,n-k-2)+pw(2,n-k);
                printf("%I64d\n",ans%MOD);
            }
        }
    }

	return 0;
}
