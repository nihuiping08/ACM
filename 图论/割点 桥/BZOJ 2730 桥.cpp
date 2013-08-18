/**************************************************************
    Problem: 2730
    User: yejinru
    Language: C++
    Result: Accepted
    Time:40 ms
    Memory:1672 kb
	
	割点、桥
****************************************************************/
 
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
 
map<int,int> ma;
 
const int MAXN = 1e4+5;
 
int dfn[MAXN],low[MAXN],dep;
int cut[MAXN],use[MAXN];
int n;
 
vector< int > adj[MAXN];
 
void dfs_1(int x){
    low[x] = dfn[x] = ++ dep;
    foreach(i,adj[x]){
        int y = adj[x][i];
        if(!dfn[y]){
            dfs_1(y);
            cmin( low[x],low[y] );
            if(low[y]>=dfn[x])
                cut[x] ++;
        }else
            cmin( low[x],dfn[y] );
    }
}
 
int tmp[MAXN],c[MAXN],sum[MAXN];
int col;
 
void dfs_2(int x){
    sum[col] ++;
    use[x] = true;
    foreach(i,adj[x]){
        int y = adj[x][i];
        if(use[y])continue;
        if(!cut[y]) dfs_2(y);
        else if(c[y]!=col){
            c[y] = col;
            tmp[col] ++;
        }
    }
}
 
void solve(int ncase){
    Clear(dfn);
    Clear(cut);
 
    rep1(i,n)
        if(!dfn[i]){
            dfs_1(i);
            cut[i] --;
        }
 
    /*
    rep1(i,n)
        if(cut[i])
            cout<<i<<" ";
    cout<<endl;
    */
 
 
    Clear(c);
    Clear(tmp);
    Clear(use);
    Clear(sum);
    col = 0;
 
    int ans = 0;
    ll tot = 1;
 
    rep1(i,n){
        if(!use[i]&&!cut[i]){
            ++ col;
            dfs_2(i);
            if(tmp[col]==1){
                ans ++;
                tot *= sum[col];
            }
        }
    }
 
    if(col==1){
        ans = 2;
        tot = ll(n-1)*n>>1;
    }
 
    printf("Case %d: %d ",ncase,ans);
    cout<<tot<<endl;
}
 
int main(){
 
#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif
 
    int m,x,y;
    int ncase = 0;
    while(cin>>m,m){
        rep(i,MAXN)
            adj[i].clear();
        n = 0;
        ma.clear();
        while(m--){
            RD2(x,y);
            if(ma[x]==0)
                ma[x] = ++ n;
            if(ma[y]==0)
                ma[y] = ++ n;
 
            x = ma[x];
            y = ma[y];
            adj[x].pb(y);
            adj[y].pb(x);
        }
        solve(++ncase);
    }
 
    return 0;
}