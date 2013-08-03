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

const int MAXN = 1e5+5;

vector<int> adj[MAXN];
int sta[MAXN],fa[MAXN],low[MAXN],dfn[MAXN],bcnt,dep,top;
bool use[MAXN];
int id[MAXN],od[MAXN],sz[MAXN];
int n,m;

void dfs(int x){
    low[x] = dfn[x] = ++ dep;
    use[x] = true;
    sta[++top] = x;
    foreach(i,adj[x]){
        int y =adj[x][i];
        if(dfn[y]==0){
            dfs(y);
            low[x] = min(low[x],low[y]);
        }else if(use[y])
            low[x] = min(low[x],dfn[y]);
    }
    if(low[x]==dfn[x]){
        ++ bcnt;
        int y;
        do{
            y = sta[top--];
            use[y] = false;
            fa[y] = bcnt;
        }while(x!=y);
    }
}

void tarjan(){
    memset(dfn,0,sizeof(dfn));
    memset(use,false,sizeof(use));
    top = dep = bcnt = 0;
    rep1(i,n)
        if(!dfn[i])
            dfs(i);
}

ll solve(){
    int x,y;
    RD2(n,m);

    rep1(i,n)
        adj[i].clear();

    rep(i,m){
        RD2(x,y);
        adj[x].pb(y);
    }

    tarjan();
    if(bcnt==1)
        return -1;

    memset(id,0,sizeof(id));
    memset(od,0,sizeof(od));
    memset(sz,0,sizeof(sz));
    rep1(x,n){
        sz[ fa[x] ] ++;
        foreach(i,adj[x]){
            int y = adj[x][i];
            if(fa[x]!=fa[y]){
                od[ fa[x] ] ++;
                id[ fa[y] ] ++;
            }
        }
    }
    ll ans = 0;
    ll tmp = (ll)n*(n-1)-m;
    rep1(i,bcnt)
        if(id[i]==0||od[i]==0)
            ans = max(ans,tmp-(ll)sz[i]*(n-sz[i]));
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    rep1(Ncase,ncase)
        printf("Case %d: %I64d\n",Ncase,solve());

	return 0;
}
