/*

题目：给出n个城市，m条无向有权路，一个单位长度需要一个单位时间，现在某个城市在t时刻是要快递，
	问最少需要多少人满足快递要求。
分析：先floyd求一边最短路，然后根据边权关系以及快递要求，以快递作为x,y部建立二分图，那么，答案
	即为最小边集覆盖
	
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
#define Clear(x) memset(x,0,sizeof(x))
/*

#pragma comment(linker, "/STACK:1024000000,1024000000")

int size = 256 << 20; // 256MB
char *p = (char*)malloc(size) + size;
__asm__("movl %0, %%esp\n" :: "r"(p) );

*/

/******** program ********************/

const int MAXN = 1005;

ll INF;
int ym[MAXN];
bool use[MAXN];
ll g[MAXN][MAXN];
ll a[MAXN],b[MAXN];
int n,m,q;
int adj[MAXN][MAXN];
int top[MAXN];

bool dfs(int x){
    rep1(i,top[x]){
        int y = adj[x][i];
        if(!use[y]){
            use[y] = true;
            if(ym[y]==-1||dfs(ym[y])){
                ym[y] = x;
                return true;
            }
        }
    }
    return false;
}

void build(){
    Clear(top);

    rep(i,q)
    rep(j,q){
        if(i==j)continue;
        if( b[i]-b[j]>=g[ a[i] ][ a[j] ] )
            adj[i][ ++top[i] ] = j;
    }
}

int solve(){
    memset(ym,-1,sizeof(ym));
    int ans = 0;
    rep(i,q){
        Clear(use);
        ans += dfs(i);
    }
    return q-ans-1;
}

void floyd(){
    rep(k,n)
        rep(i,n)
            rep(j,n)
                cmin( g[i][j],g[i][k]+g[k][j] );
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    rep1(Ncase,ncase){
        RD3(n,m,q);
        int x,y;
        ll z;

        memset(g,0x3f,sizeof(g));
        rep(i,n)
            g[i][i] = 0;
        INF = g[0][1];

        while(m--){
            RD2(x,y);
            scanf("%I64d",&z);
            cmin(g[x][y],z);
            cmin(g[y][x],z);
        }
        rep(i,q)
            scanf("%I64d%I64d",&a[i],&b[i]);

        floyd();
        build();
        solve();
        printf("Case %d: %d\n",Ncase,solve());
    }

	return 0;
}
