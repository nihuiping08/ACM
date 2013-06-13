/*

题目：AX+BY+C = 0，问在[-5e18,5e18]中是否有解
分析：Ex_gcd求解即可

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

const ll INF = 5e18;

void ex_gcd(ll a,ll b,ll &x,ll &y,ll &gcd){
    if(b==0){
        x = 1;
        y = 0;
        gcd = a;
    }else{
        ex_gcd(b,a%b,y,x,gcd);
        y -= x*(a/b);
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    ll a,b,c;
    while(cin>>a>>b>>c){
        ll x,y,gcd;
        ex_gcd(a,b,x,y,gcd);
        if(c%gcd){
            puts("-1");
            continue;
        }
        c *= -1;
        c /= gcd;
        if( c && ( abs(INF/c)<abs(x) || abs(INF/c)<abs(y) ) )
            puts("-1");
        else
            cout<<x*c<<" "<<y*c<<endl;
    }

	return 0;
}
