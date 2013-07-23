/*

暴力枚举最小值，再暴力枚举次小值即可。

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
#define cmax(x,y) x = max(x,y)
#define cmin(x,y) x = min(x,y)

/******** program ********************/

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    ll n;
    while(cin>>n){
        ll MAX = 0 , MIN = 1e15;
        for(ll i=1;i*i<=n;i++){
            if(n%i)
                continue;
            ll t = n/i;
            for(ll j=i;j*j<=t;j++){
                if(t%j)
                    continue;
                ll k = t/j;
                if(j>k)
                    continue;
                ll tmp = i*j*k;
                cmax(MAX, (i+1)*(j+2)*(k+2)-tmp );
                cmax(MAX, (k+1)*(j+2)*(i+2)-tmp );
                cmax(MAX, (j+1)*(i+2)*(k+2)-tmp );

                cmin(MIN, (i+1)*(j+2)*(k+2)-tmp );
                cmin(MIN, (k+1)*(j+2)*(i+2)-tmp );
                cmin(MIN, (j+1)*(i+2)*(k+2)-tmp );
            }
        }
        cout<<MIN<<" "<<MAX<<endl;
    }

	return 0;
}
