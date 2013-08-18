/*

题意：LCA问题
解法：tarjan或RMQ，输入需要留意

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

int n;
vector< int > adj[MAXN];
int dp[MAXN][20];
int dis[MAXN];

int depth;
int b[MAXN],bn;    //深度序列
int f[MAXN];    //对应深度序列中的结点编号
int p[MAXN];    //结点在深度序列中的首位置

int ans[MAXN];
int id[MAXN];

void dfs(int x,int fa){
    int tmp = ++ depth;
    b[++bn] = tmp;
    f[tmp] = x;
    p[x] = bn;
    foreach(i,adj[x]){
        int y = adj[x][i];
        if (y==fa) continue;
        dfs(y,x);
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

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n){
        rep1(i,n)
            adj[i].clear();
        int x,k,y;

        memset(id,0,sizeof(id));
        rep1(i,n){
            scanf("%d:(%d)",&x,&k);
            while(k--){
                RD(y);
                adj[x].pb(y);
                id[y] ++;
            }
        }

        int root = 1;
        rep1(i,n)
            if(id[i]==0)
                root = i;
        //cout<<"root "<<root<<endl;

        depth = bn = 0;
        dfs(root,0);
        rmq_init(bn);

        memset(ans,0,sizeof(ans));

        RD(k);
        while(k--){
            scanf(" (%d %d) ",&x,&y);
            //cout<<x<<" "<<y<<endl;
            int t = lca(x,y);
            ans[t] ++;
        }
        rep1(i,n)
            if(ans[i])
                printf("%d:%d\n",i,ans[i]);
    }

    return 0;
}
