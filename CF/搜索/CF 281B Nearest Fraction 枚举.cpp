/*

题目：给出x,y,n，找出使得|x/y-a/b|最小的a,b值，a>=0,1<=b<=n
分析：先枚举b的值，算出a的近似值，然后在一定范围内枚举a的值，更新答案

*/
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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)



int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    ll n,x,y;
    while(cin>>x>>y>>n){
        ll ans_a = 100000,ans_b = 1;
        double tmp = x*1.0/y;
        for(ll b=1;b<=n;b++){
            ll ret = max(ll(0),(ll)(tmp*b)-5);

            for(ll a=ret;a<=ret+20;a++){
                if(__gcd(a,b)!=1)
                    continue;

                ll u = x*b-a*y;
                ll v = x*ans_b-ans_a*y;
                u = max(u,-u);
                v = max(v,-v);
                if(v*b>u*ans_b){
                    ans_a = a;
                    ans_b = b;
                }
            }
        }
        cout<<ans_a<<"/"<<ans_b<<endl;
    }

	return 0;
}
