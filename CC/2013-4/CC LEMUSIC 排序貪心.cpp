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

const int MAXN = 1e5+5;

int num[MAXN],ha[MAXN],n;
bool use[MAXN];

struct node{
    int id,b,len;
    friend bool operator < (node a,node b){
        return a.b<b.b || (a.b==b.b&&a.len<b.len);
    }
}p[MAXN];

struct pp{
    int b,len;
    pp(){}
    pp(node a){
        b = a.b;
        len = a.len;
    }
    friend bool operator < (pp a,pp b){
        return a.len<b.len;
    }
}s[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    while(ncase--){
        RD(n);
        rep1(i,n){
            RD2(p[i].b,p[i].len);
            p[i].id = i;
        }

        sort(p+1,p+n+1);

        int m = 0;
        memset(use,false,sizeof(use));
        s[++m] = pp(p[1]);
        use[p[1].id] = true;
        REP(i,2,n)
            if(p[i].b!=p[i-1].b){
                s[++m] = pp(p[i]);
                use[p[i].id] = true;
            }
        sort(s+1,s+m+1);
        ll ans = 0;
        rep1(i,m)
            ans += ll(i)*s[i].len;
        rep1(i,n)
            if(!use[p[i].id])
                ans += ll(m) * p[i].len;
        cout<<ans<<endl;
    }

	return 0;
}
