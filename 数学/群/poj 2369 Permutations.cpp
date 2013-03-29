/*

題目：問置換群的循環節
分析：并查集，答案為所有集合大小的最小公倍數

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
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

const int MAXN = 1005;

int sz[MAXN],fa[MAXN];

ll gcd(ll x,ll y){
    return x==0?y:gcd(y%x,x);
}
int find_set(int x){
    if(x!=fa[x])
        fa[x] = find_set(fa[x]);
    return fa[x];
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n;
    while(~RD(n)){
        rep1(i,n)
            fa[i] = i;
        memset(sz,0,sizeof(sz));
        int x;
        rep1(i,n){
            RD(x);
            int px = find_set(i);
            int py = find_set(x);
            if(px!=py)
                fa[px] = py;
        }
        rep1(i,n)
            sz[find_set(i)] ++;
        vector<int> vec;
        rep1(i,n){
            x = find_set(i);
            if(sz[x]==0)
                continue;
            vec.pb(sz[x]);
            sz[x] = 0;
        }
        ll ans = 1;
        foreach(i,vec){
            ll g = gcd(vec[i],ans);
            ans = ans/g*vec[i];
        }
        cout<<ans<<endl;
    }

	return 0;
}
