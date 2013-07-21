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

bool cc(ll now){
    if(now<0)return false;

    ll l = 1 , r = (ll)sqrt(now)*5;

    while(l<=r){
        ll mid = (l+r)/2;
        ll tmp = (mid+1)*mid/2;
        if( tmp==now )
            return true;
        else if( tmp>now )
            r = mid-1;
        else
            l = mid+1;
    }
    return false;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    ll n;
    while(cin>>n){
        ll len = (ll)sqrt(n)*2;
        bool ok = false;
        for(ll i=1;i<=len;i++){
            if(cc( n-i*(i+1)/2 )){
                ok = true;
                break;
            }
        }
        ok?puts("YES"):puts("NO");
    }

	return 0;
}
