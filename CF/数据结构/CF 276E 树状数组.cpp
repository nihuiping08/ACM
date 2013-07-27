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

const int MAXN = 1e5+5;

vector< vector<ll> > c;
int fa[MAXN],dis[MAXN];
vector<int> adj[MAXN];

int lowbit(int x){
    return x & -x;
}

void modify(int id,int st,int ed,ll val){
    if(st>ed)return;
    int mx = c[id].size();
    for(int i=ed+1;i<mx;i+=lowbit(i))
        c[id][i] -= val;
    for(int i=st;i<mx;i+=lowbit(i))
        c[id][i] += val;
}

ll ask(int id,int ed){
    ll ret = 0;
    for(int i=ed;i>0;i-=lowbit(i))
        ret += c[id][i];
    return ret;
}

void dfs(int x,int pa,int id,int dep){
    dis[x] = dep;
    fa[x] = id;
    c[id].pb(0);
    foreach(i,adj[x]){
        int y = adj[x][i];
        if(y==pa)continue;
        dfs(y,x,id,dep+1);
    }
}


int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,m;
    while(cin>>n>>m){
        c.clear();
        rep1(i,n)
            adj[i].clear();
        int x,y;
        REP(i,2,n){
            RD2(x,y);
            adj[x].pb(y);
            adj[y].pb(x);
        }

        c.resize(adj[1].size()+10);
        foreach(i,adj[1]){
            c[i+1].pb(0);
            dfs(adj[1][i],1,i+1,1);
        }
        c[0].resize( n+10,0 );

        int op,v,d;
        ll rootSum = 0;
        while(m--){
            RD(op);
            if(op){
                RD(x);
                if(x==1)
                    cout<<rootSum<<endl;
                else
                    cout<<ask( 0,dis[x] )+ask(fa[x],dis[x])<<endl;
            }else{
                RD3(x,v,d);
                if(x==1){
                    rootSum += v;
                    modify(0,1,d,v);
                }else{
                    if(d<dis[x])
                        modify( fa[x],dis[x]-d,dis[x]+d,v );
                    else{
                        rootSum += v;
                        modify( fa[x],1,d+dis[x],v );
                        modify( fa[x],1,d-dis[x],-v );
                        modify( 0,1,d-dis[x],v );
                    }
                }
            }
        }
    }

	return 0;
}
