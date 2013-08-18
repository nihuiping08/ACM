/*

给出带边权的树，问任意连接点的距离

lca..

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
#define fir first
#define sec second

/******** program ********************/

const int MAXN = 200005;

int n,rt,m;
vector< PII > adj[MAXN];
int dp[MAXN][20];
int dis[MAXN];

int depth;
int b[MAXN],bn;    //深度序列
int f[MAXN];    //对应深度序列中的结点编号
int p[MAXN];    //结点在深度序列中的首位置

void dfs(int x,int fa,int sum){
    dis[x] = sum;
    int tmp = ++ depth;
    b[++bn] = tmp;
    f[tmp] = x;
    p[x] = bn;
    foreach(i,adj[x]){
        int y = adj[x][i].first;
        if (y==fa) continue;
        dfs(y,x,sum+adj[x][i].second);
        b[++bn] = tmp;
    }
}

void rmq_init(int n){ //以深度序列做rmq
    rep1(i,n)
        dp[i][0]=b[i];
    int m = floor(log(n*1.0)/log(2.0));
    rep1(j,m)
      for (int i=1; i<=n-(1<<j)+1; i++)
          dp[i][j] = min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
}

int rmq(int l,int r){
    int k = floor(log((r-l+1)*1.0)/log(2.0));
    return min( dp[l][k] , dp[r-(1<<k)+1][k] );
}

int lca(int a,int b){
    if (p[a]>p[b])
        swap(a,b);
    return f[ rmq(p[a],p[b]) ];
}

int cc(int x,int y){
    return dis[x]+dis[y]-2*dis[ lca(x,y) ];
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m){
        rep1(i,n)
            adj[i].clear();
        depth = bn = 0;
        int x,y,z;
        char op[2];
        while(m--){
            RD3(x,y,z);
            scanf("%s",op);
            adj[x].pb( MP(y,z) );
            adj[y].pb( MP(x,z) );
        }
        rt = 1;
        dfs(1,0,0);
        rmq_init(bn);
        RD(m);
        while(m--){
            RD2(x,y);
            printf("%d\n",cc(x,y));
        }
    }

    return 0;
}
