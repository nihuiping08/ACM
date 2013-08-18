/*

题目：输出无向图的所有桥

模板题

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

const int MAXN = 1e4+5;

vector< PII > adj[MAXN],ans;
int low[MAXN],dfn[MAXN],fa[MAXN],dep;
bool is[MAXN*10];

int find_set(int x){
    if(fa[x]!=x)
        fa[x] = find_set(fa[x]);
    return fa[x];
}

void dfs(int x,int fid){
    low[x] = dfn[x] = ++ dep;
    foreach(i,adj[x]){
        int y = adj[x][i].first;
        int id = abs( adj[x][i].second );
        if(id==fid)continue;
        if(!dfn[y]){
            dfs(y,id);
            cmin( low[x],low[y] );

            if(low[y]>dfn[x]){
                // is bredage
                is[id] = 1;
            }else{
                int px = find_set(x);
                int py = find_set(y);
                if(px!=py)
                    fa[py] = px;
            }
        }else
            cmin( low[x],dfn[y] );
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n;
    while(cin>>n){
        rep(i,n)
            adj[i].clear();
        Clear(is);

        int tot = 0;
        int x,k,y;
        rep1(i,n){
            scanf("%d (%d)",&x,&k);
            //cout<<x<<" "<<k<<endl;
            while(k--){
                RD(y);
                if(x>y)continue;
                //cout<<x<<" "<<y<<endl;
                ++ tot;
                adj[x].pb( MP(y,tot) );
                adj[y].pb( MP(x,-tot) );
            }
        }

        Clear(dfn);
        Clear(is);
        rep(i,n)
            fa[i] = i;

        rep(i,n)
            if(!dfn[i])
                dfs(i,-1);

        ans.clear();
        rep(x,n){
            foreach(i,adj[x]){
                int id = adj[x][i].second;
                if(id<0)continue;
                if(is[id])
                    ans.pb( MP(x,adj[x][i].first) );
            }
        }

        sort( All(ans) );
        printf("%d critical links\n",ans.size());
        foreach(i,ans)
            printf("%d - %d\n",ans[i].first,ans[i].second);
        puts("");
    }

	return 0;
}
