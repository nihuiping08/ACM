/*

題目：給出一棵樹，問路徑長為k的點對的數目
分析：樹上二維DP,dp[n][num]表示節點n剩餘num長度的路徑
    則他可以是由兒子轉移過來，或者有一個節點為父節點的子節點轉移過來
    所以我們可以知道轉移方程為
    down[x][j] = sigma( down[y][j] )表示由兒子節點轉移過來
    dp[x][j] = dp[fa][j-1]+down[fa][j-1]-down[x][j-2](表示需要減掉這條路徑)

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

#define lx(x) (x<<1)
#define rx(x) (x<<1|1)
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

const int MAXN = 50005;

ll d[MAXN][502],up[MAXN][502];
vector<int> vec[MAXN];
int n,m;

void dfs_1(int x,int fa){
    d[x][0] = 1;
    foreach(i,vec[x]){
        int y = vec[x][i];
        if(y==fa)   continue;
        dfs_1(y,x);
        rep(j,m)
            d[x][j+1] += d[y][j];
    }
}

void dfs_2(int x,int fa){
    if(fa)
        rep(j,m)
            up[x][j+1] += up[fa][j]+d[fa][j]-(j?d[x][j-1]:0);
    foreach(i,vec[x])
        if( vec[x][i]!=fa )
            dfs_2( vec[x][i],x );
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD2(n,m)){
        rep1(i,n)
            vec[i].clear();
        memset(d,0,sizeof(d));
        memset(up,0,sizeof(up));
        int x,y;
        int tmp = n-1;
        rep(i,tmp){
            RD2(x,y);
            vec[x].pb(y);
            vec[y].pb(x);
        }
        dfs_1(1,0);
        dfs_2(1,0);

        ll ans = 0;
        rep1(i,n)
            ans += d[i][m]+up[i][m];
        cout<<ans/2<<endl;
    }

	return 0;
}
