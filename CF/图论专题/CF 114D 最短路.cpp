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

const int MAXN = 2e5+5;

vector< PII > adj[MAXN];
int dis[MAXN];
bool use[MAXN];
int n,s,m,len;

struct node{
    int x,y,d;
    friend bool operator < (node a,node b){
        return a.x<b.x||
            (a.x==b.x&&a.y<b.y)||
            (a.x==b.x&&a.y==b.y&&a.d<b.d);
    }
    node(){}
    node(int i,int j,int k){
        x = i;
        y = j;
        d = k;
    }
};

void spfa(){
    memset(dis,0x7f,sizeof(dis));
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    memset(use,false,sizeof(use));
    while(!q.empty()){
        int x = q.front();
        q.pop();
        use[x] = false;
        foreach(i,adj[x]){
            int y = adj[x][i].first;
            int t = adj[x][i].second+dis[x];
            if(dis[y]>t){
                dis[y] = t;
                if(!use[y]){
                    use[y] = true;
                    q.push(y);
                }
            }
        }
    }
}

void solve(){
    int ans = 0;
    map<node,bool> ma;
    rep1(x,n){
        if(dis[x]==len)
            ans ++;
        if(dis[x]>=len)continue;

        foreach(i,adj[x]){
            int y = adj[x][i].first;
            int tot = adj[x][i].second+dis[x];
            if(tot<len)continue;
            int res = len-dis[x];
            if( res+dis[x]>dis[y]+adj[x][i].second-res )continue;
            if( res==0 ||  adj[x][i].second-res==0 )continue;
            if( ma[ node(x,y,res) ] )continue;
            ma[ node(x,y,res) ] = ma[ node(y,x,adj[x][i].second-res) ] = true;
            ans ++;
        }
    }
    cout<<ans<<endl;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m>>s){
        int x,y,w;
        rep1(i,n)
            adj[i].clear();
        while(m--){
            RD3(x,y,w);
            adj[x].pb( MP(y,w) );
            adj[y].pb( MP(x,w) );
        }
        RD(len);

        spfa();
        solve();
    }

	return 0;
}
