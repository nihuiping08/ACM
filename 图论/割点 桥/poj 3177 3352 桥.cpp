/*

题目：给出一个无向图，问至少需要添加多少条边使得图中删除任意一条边图还是连通图
分析：求桥，把双连通分量缩点之后形成一棵搜索树，（树的叶子节点的个数+1）/2即为答案

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

const int MAXN = 2005;

vector< PII > adj[MAXN];
int low[MAXN],dfn[MAXN],dep;
int fa[MAXN];
bool is[MAXN];
int cnt[MAXN];

int find_set(int x){
    if(fa[x]!=x)
        fa[x] = find_set(fa[x]);
    return fa[x];
}

void dfs(int x,int fid){
    low[x] = dfn[x] = ++dep;
    foreach(i,adj[x]){
        int y = adj[x][i].first;
        int id = adj[x][i].second;
        if(!dfn[y]){
            dfs(y,id);
            cmin( low[x],low[y] );
            if(dfn[x]<low[y]){
                //cout<<"qiao   "<<x<<" "<<y<<endl;
                is[id] = is[id^1] = true;
            }else{
                int px = find_set(x);
                int py = find_set(y);
                if(px!=py)fa[px] = py;
            }
        }else if( id!=fid )
            cmin( low[x],dfn[y] );
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int x,y,n,m;
    while(cin>>n>>m){
        rep1(i,n)
            adj[i].clear();
        int tot = 1;
        rep1(i,m){
            RD2(x,y);
            adj[x].pb( MP(y,++tot) );
            adj[y].pb( MP(x,tot) );
        }

        rep1(i,n)
            fa[i] = i;
        Clear(is);
        Clear(dfn);
        dep = 0;
        dfs(1,0);

        Clear(cnt);
        rep1(x,n){
            int px = find_set(x);
            foreach(i,adj[x]){
                int y = adj[x][i].first;
                int py = find_set(y);
                if(px!=py)
                    cnt[py]++;
            }
        }
        int ans = 0;
        rep1(x,n){
            int px = find_set(x);
            ans += cnt[px]==1;
            cnt[px] = 0;
        }
        //cout<<ans<<" ";
        cout<<(ans+1)/2<<endl;
    }

	return 0;
}
