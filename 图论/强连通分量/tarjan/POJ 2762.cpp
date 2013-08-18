/*

题目：判断是否任意两个点可以单向走动
分析：tarjan缩点+dp求最长链

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

const int MAXN = 1005;

int fa[MAXN],sta[MAXN],low[MAXN],dfn[MAXN],bcnt,dep,top;
bool use[MAXN];
vector<int> edge[MAXN],adj[MAXN];
int id[MAXN],n,m;
int sz[MAXN];

void dfs(int x){
    use[x] = true;
    low[x] = dfn[x] = ++ dep;
    sta[++top] = x;
    int y;
    foreach(i,edge[x]){
        y = edge[x][i];
        if(!dfn[y]){
            dfs(y);
            cmin( low[x],low[y] );
        }else if(use[y])
            cmin( low[x],dfn[y] );
    }
    if(low[x]==dfn[x]){
        ++ bcnt;
        do{
            y = sta[top--];
            use[y] = false;
            fa[y] = bcnt;
        }while(x!=y);
    }
}

int DP(int x){
    int ans = 0;
    foreach(i,adj[x])
        ans = max( ans , DP(adj[x][i]) );
    return ans+sz[x];
}

void tarjan(){
    Clear(use);
    Clear(dfn);
    top = bcnt = dep = 0;

    rep1(i,n)
        if(!dfn[i])
            dfs(i);

    Clear(sz);
    Clear(id);

    rep1(x,n){
        sz[ fa[x] ] ++;
        foreach(i,edge[x]){
            int y = edge[x][i];
            if(fa[x]!=fa[y]){
                id[ fa[y] ] ++;
                adj[ fa[x] ].pb( fa[y] );
            }
        }
    }

    int ans = 0;
    rep1(i,bcnt)
        if(id[i]==0)
            ans = max(ans, DP(i) );
    if(ans==n)
        puts("Yes");
    else
        puts("No");
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase,x,y;
    RD(ncase);
    while(ncase--){
        RD2(n,m);
        rep1(i,n){
            adj[i].clear();
            edge[i].clear();
        }
        rep1(i,m){
            RD2(x,y);
            edge[x].pb(y);
        }
        tarjan();
    }

	return 0;
}
