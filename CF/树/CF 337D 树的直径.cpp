/*

题目：给出树上的m个点，求到这m个点的距离不大于d的点的个数

分析：对于这m个点组成的一棵子树求一遍直径，然后遍历一遍即可。

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
/*

#pragma comment(linker, "/STACK:1024000000,1024000000")

int size = 256 << 20; // 256MB
char *p = (char*)malloc(size) + size;
__asm__("movl %0, %%esp\n" :: "r"(p) );

*/

/******** program ********************/

const int MAXN = 100005;

vector<int> adj[MAXN];
bool good[MAXN];
int n,m,d;

int MAX , pos;
void dfsR(int x,int fa,int dep){
    if(good[x]&&dep>MAX){
        MAX = dep;
        pos = x;
    }
    foreach(i,adj[x]){
        int y = adj[x][i];
        if(y!=fa)
            dfsR(y,x,dep+1);
    }
}

int dis[MAXN];
bool is[MAXN];

bool dfs(int x,int fa,int end,int s,int t){
    is[x] = true;
    dis[x] = max(s,t);
    if(x==end)
        return true;
    foreach(i,adj[x]){
        int y = adj[x][i];
        if(y!=fa&&dfs(y,x,end,s+1,t-1))
            return true;
    }
    is[x] = false;
    return false;
}

int ans;
void dfsAns(int x,int fa,int s,int t){
    if(max(s,t)<=d)ans ++;
    foreach(i,adj[x]){
        int y = adj[x][i];
        if(y==fa)continue;
        if(is[y])
            dfsAns(y,x,s+1,t-1);
        else
            dfsAns(y,x,s+1,t+1);
    }
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m>>d){
        Clear(good);
        int x,y;
        rep(i,m){
            RD(x);
            good[x] = true;
        }
        rep1(i,n)
            adj[i].clear();
        REP(i,2,n){
            RD2(x,y);
            adj[x].pb(y);
            adj[y].pb(x);
        }

        MAX = 0;
        dfsR(1,0,0);
        MAX = 0;
        int rx = pos;
        dfsR(rx,0,0);
        int ry = pos;
        if(MAX>2*d){
            puts("0");
            continue;
        }

        memset(dis,0,sizeof(dis));
        dfs(rx,0,ry,0,MAX);

        ans = 0;
        dfsAns(rx,0,0,MAX);
        cout<<ans<<endl;
    }

    return 0;
}
