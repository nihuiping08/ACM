/*

題目：給出n天帳本，a,b,c:表示從第a天到第b天的帳為c。問帳本是否有假
分析：經典并查集。在路徑壓縮的時候，需要注意減掉另一個集合的和

*/
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

const int MAXN = 2005;

int fa[MAXN],sz[MAXN];

int find_set(int x){
    if(fa[x]!=x){
        int tmp = find_set(fa[x]);
        sz[x] += sz[fa[x]];
        fa[x] = tmp;
    }
    return fa[x];
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    while(ncase--){
        int n,m,x,y,z;
        RD2(n,m);
        rep(i,n+1)
            fa[i] = i;
        memset(sz,0,sizeof(sz));
        bool ok = false;
        while(m--){
            RD3(x,y,z);
            if(ok) continue;
            int px = find_set(--x);
            int py = find_set(y);
            if(px!=py){
                fa[py] = px;
                sz[py] = sz[x]+z-sz[y];
            }else if(sz[x]+z!=sz[y])
                ok = true;
        }
        ok?puts("false"):puts("true");
    }
	return 0;
}
