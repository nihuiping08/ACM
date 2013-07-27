/*

在树的任意两点所在的所有树的边权加一，输出最后所有的边权	

LCA。我们可以离线操作，把所有的询问直接求出LCA，然后用数组
dis[x] ++ ,   dis[y]++,
dis[LCA(x,y)]  -=  2
最后DFS统计一下答案

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

const int MAXN = 2e5+5;

vector< PII > edge[MAXN];
vector< PII > ask[MAXN];
int fa[MAXN];
bool use[MAXN];
int pa[MAXN];
int n,m;
int dis[MAXN];
int a[MAXN],b[MAXN];
int ans[MAXN];

int find_set(int x){
    if(fa[x]!=x)
        fa[x] = find_set(fa[x]);
    return fa[x];
}

void lca(int x,int f){
    //cout<<"x = "<<x<<endl;
    use[x] = true;
    fa[x] = x;
    foreach(i,ask[x]){
        int y = ask[x][i].first;
        int id = ask[x][i].second;
        //cout<<"dsadsa = "<<x<<" "<<y<<" "<<id<<endl;
        if(use[y])
            pa[id] = find_set(y);
    }

    foreach(i,edge[x]){
        int y = edge[x][i].first;
        //cout<<"y = "<<y<<endl;
        if(use[y])continue;
        lca(y,x);
        fa[y] = x;
    }
}

void dfs(int x,int f){
    foreach(i,edge[x]){
        int y = edge[x][i].first;
        if(y==f)continue;
        dfs(y,x);
        int id = edge[x][i].second;
        dis[x] += dis[y];
        ans[id] = dis[y];
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n){
        int x,y;
        rep(i,MAXN){
            edge[i].clear();
            ask[i].clear();
        }

        memset(use,false,sizeof(use));
        REP(i,2,n){
            RD2(x,y);
            edge[x].pb( MP(y,i) );
            edge[y].pb( MP(x,i) );
        }
        RD(m);
        rep1(i,m){
            RD2(x,y);
            a[i] = x;
            b[i] = y;
            ask[x].pb( MP(y,i) );
            ask[y].pb( MP(x,i) );
        }
        lca(1,0);

        memset(dis,0,sizeof(dis));
        rep1(i,m){
            x = a[i];
            y = b[i];
            dis[x] ++;
            dis[y] ++;
            dis[ pa[i] ] -= 2;
            //cout<<x<<" "<<y<<" "<<pa[i]<<endl;
        }

        dfs(1,0);

        REP(i,2,n)
            printf("%d ",ans[i]);
        puts("");
    }

	return 0;
}
