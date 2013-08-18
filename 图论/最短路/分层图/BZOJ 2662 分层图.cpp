/*

增加一维表示多余的状态，最短路松弛时变形

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

const int MAXN = 55;
const int INF = 1e9;

vector<PII> adj[MAXN];
int dis[MAXN][MAXN];
bool use[MAXN];
int n,m;

void spfa(){
    rep1(i,n)
        rep(j,m+1)
            dis[i][j] = INF;
    Clear(use);
    Clear(dis[1]);

    queue< int > q;
    q.push( 1 );
    while(q.size()){
        int x = q.front();
        q.pop();
        use[x] = false;
        foreach(i,adj[x]){
            int y = adj[x][i].first;
            int d = adj[x][i].second;
            rep(j,m+1){
                if(j&&dis[y][j]>dis[x][j-1]+d/2){
                    dis[y][j] = dis[x][j-1]+d/2;
                    if(!use[y]){
                        q.push(y);
                        use[y] = true;
                    }
                }
                if(dis[y][j]>dis[x][j]+d){
                    dis[y][j] = dis[x][j]+d;
                    if(!use[y]){
                        q.push(y);
                        use[y] = true;
                    }
                }
            }
        }
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int k;
    int x,y,z;
    while(cin>>n>>k>>m){
        rep1(i,n)
            adj[i].clear();
        while(k--){
            RD3(x,y,z);
            adj[x].pb( MP(y,z) );
            adj[y].pb( MP(x,z) );
        }
        spfa();
        int ans = INF;
        rep(i,m+1)
            cmin(ans,dis[n][i]);
        cout<<ans<<endl;
    }

	return 0;
}
