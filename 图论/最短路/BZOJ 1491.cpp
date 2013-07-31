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
#define fir first
#define sec second
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/

const int MAXN = 105;
const int INF = 1e9;

ll dp[MAXN][MAXN];
ll g[MAXN][MAXN];
int n,m;

void floyd(){
    rep1(k,n)
    rep1(i,n)
    rep1(j,n)
    if(i!=j&&i!=k&&j!=k){
        if(g[i][j]==g[i][k]+g[k][j])
            dp[i][j] += dp[i][k]*dp[k][j];
        else if(g[i][j]>g[i][k]+g[k][j]){
            g[i][j] = g[i][k]+g[k][j];
            dp[i][j] = dp[i][k]*dp[k][j];
        }
    }

    rep1(k,n){
        double ans = 0;
        rep1(i,n)
        if(i!=k)
        rep1(j,n)
        if(i!=j&&j!=k&&g[i][j]==g[i][k]+g[k][j])
            ans += dp[i][k]*dp[k][j]*1.0/dp[i][j];
        printf("%.3lf\n",ans);
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m){
        int x,y,w;

        rep1(i,n)
        rep1(j,n)
        g[i][j] = INF;

        while(m--){
            RD3(x,y,w);
            g[x][y] = g[y][x] = w;
            dp[x][y] = dp[y][x] = 1;
        }

        floyd();
    }

	return 0;
}
