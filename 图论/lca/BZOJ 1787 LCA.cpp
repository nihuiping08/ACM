/*

题目：在树上找一个聚合点，使得三个点与他的距离最短
分析：显然聚合点在其中两个的lca上，使用在线的lca求法即可。

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
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/


const int MAXN = 1000005;

int n,rt;
vector< int > adj[MAXN];
int dp[MAXN][20];
int dis[MAXN];

int depth;
int b[MAXN],bn;    //深度序列
int f[MAXN];    //对应深度序列中的结点编号
int p[MAXN];    //结点在深度序列中的首位置
int dep[MAXN];

void dfs(int x,int fa,int du){
    int tmp = ++ depth;
    b[++bn] = tmp;
    f[tmp] = x;
    p[x] = bn;
    dep[x] = du;
    foreach(i,adj[x]){
        int y = adj[x][i];
        if (y==fa) continue;
        dfs(y,x,du+1);
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

int cc(int x,int y,int z,int k){
    x = dep[x]+dep[k]-2*dep[ lca(x,k) ];
    y = dep[y]+dep[k]-2*dep[ lca(y,k) ];
    z = dep[z]+dep[k]-2*dep[ lca(z,k) ];

    return x+y+z;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,m;
    while(cin>>n>>m){
        rep1(i,n)
            adj[i].clear();
        int x,y,z;
        REP(i,2,n){
            RD2(x,y);
            adj[x].pb(y);
            adj[y].pb(x);
        }
        rt = 1;
        depth = bn = 0;
        dfs(1,0,1);
        rmq_init(bn);

        while(m--){
            RD3(x,y,z);

            int pos = -1;
            int ans = 100000000;

            int k = lca(x,y);
            int t = cc(x,y,z,k);
            if(t<ans){
                ans = t;
                pos = k;
            }

            k = lca(x,z);
            t = cc(x,y,z,k);
            if(t<ans){
                ans = t;
                pos = k;
            }

            k = lca(y,z);
            t = cc(x,y,z,k);
            if(t<ans){
                ans = t;
                pos = k;
            }

            printf("%d %d\n",pos,ans);
        }

    }

	return 0;
}
