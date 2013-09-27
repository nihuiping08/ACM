/*

题目：

zdf给出的题目翻译：

从前有一个富饶的国度，在这里人们可以进行自由的交易。这个国度形成一个n个点的无向图，每个
点表示一个城市，并且有一个权值w[i]，表示这个城市出售或收购这个权值的物品。又到了一年一
次团圆的日子，所有外出打工的人都急忙赶着回家。现在有m个人，给出每个人的工作地点和家的
编号，让你求出每个人在回家的路上通过倒卖物品获得的最大收益，因为要急忙赶着回家，所以
他们一定会选择最短的路程，并且只进行一次倒卖（即最多买一次、卖一次）。

 

分析：

　　与倍增求lca相似，额外记录四个值：

　　dmax[x][i]：从x的第2^i父亲到该节点的节点最大权值

　　dmin[x][i]：从x的第2^i父亲到该节点的节点最小权值

　　up[x][i]：从x节点到x的第2^i父亲的路径的最大利润

　　down[x][i]：从x的第2^i父亲到x节点的路径的最大利润

 

　　转移时跟普通的倍增相似，在求lca时注意方向，先求lca，然后让x沿着根的方向向上走到lca，
记录一下最小值，并且更新答案。再让y沿着根的方向向上走到lca，记录一下最大值，并且更新答案。
把答案跟最大值-最小值比较更新。因为答案可能会出现在x到lca或者lca到y的一侧路径上，或者在x
到y的路径且经过lca。

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
#define lson rt<<1
#define rson rt<<1|1

/*

#pragma comment(linker, "/STACK:1024000000,1024000000")

int size = 256 << 20; // 256MB
char *p = (char*)malloc(size) + size;
__asm__("movl %0, %%esp\n" :: "r"(p) );

*/

char IN;
bool NEG;
inline void Int(int &x){
    NEG = 0;
    while(!isdigit(IN=getchar()))
        if(IN=='-')NEG = 1;
    x = IN-'0';
    while(isdigit(IN=getchar()))
        x = x*10+IN-'0';
    if(NEG)x = -x;
}
inline void LL(ll &x){
    NEG = 0;
    while(!isdigit(IN=getchar()))
        if(IN=='-')NEG = 1;
    x = IN-'0';
    while(isdigit(IN=getchar()))
        x = x*10+IN-'0';
    if(NEG)x = -x;
}

/******** program ********************/

const int MAXN = 51005;
const int LOG = 18;

vector<int> adj[MAXN];
int p[MAXN][LOG+1],dep[MAXN];
int dmax[MAXN][LOG+1],dmin[MAXN][LOG+1],up[MAXN][LOG+1],down[MAXN][LOG+1];
int val[MAXN],n;

void dfs(int x,int fa){
    dep[x] = dep[fa]+1;

    dmax[x][0] = max(val[x],val[fa]);
    dmin[x][0] = min(val[x],val[fa]);
    up[x][0] = max(0,val[fa]-val[x]);
    down[x][0] = max(0,val[x]-val[fa]);
    p[x][0] = fa;

    rep1(i,LOG){
        int pa = p[x][i-1];
        p[x][i] = p[pa][i-1];

        dmax[x][i] = max(dmax[x][i-1],dmax[pa][i-1]);
        dmin[x][i] = min(dmin[x][i-1],dmin[pa][i-1]);

        up[x][i] = max(up[x][i-1],up[pa][i-1]);
        cmax(up[x][i],dmax[pa][i-1]-dmin[x][i-1]);

        down[x][i] = max(down[x][i-1],down[pa][i-1]);
        cmax(down[x][i],dmax[x][i-1]-dmin[pa][i-1]);
    }

    foreach(i,adj[x])
        if(adj[x][i]!=fa)
            dfs(adj[x][i],x);
}

int lca(int x,int y){
    if(dep[x]>dep[y])swap(x,y);
    if(dep[x]<dep[y]){
        int del = dep[y]-dep[x];
        rep(i,LOG)
            if( del>>i & 1 )
                y = p[y][i];
    }
    if(x!=y){
        for(int i=LOG-1;i>=0;i--)
            if( p[x][i]!=p[y][i] ){
                x = p[x][i];
                y = p[y][i];
            }
        x = p[x][0];
        y = p[y][0];
    }
    return x;
}

void climb(int x,int goal,bool UP,int &ans,int &tmp){
    tmp = val[x];
    int d = dep[x]-dep[goal];
    for(int i=LOG;i>=0;i--)
        if(d>>i&1){
            if(UP){
                cmax(ans,dmax[x][i]-tmp);
                cmin(tmp,dmin[x][i]);
                cmax(ans,up[x][i]);
            }else{
                cmax(ans,tmp-dmin[x][i]);
                cmax(tmp,dmax[x][i]);
                cmax(ans,down[x][i]);
            }
            x = p[x][i];
        }
}

int solve(int x,int y){
    int an = lca(x,y);
    int ans = 0;
    int px,py;

    climb(x,an,1,ans,px);
    climb(y,an,0,ans,py);

    return max( ans,py-px );
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    while(~RD(n)){
        rep1(i,n)
            adj[i].clear();
        rep1(i,n)
            RD(val[i]);
        int x,y,m;
        REP(i,2,n){
            RD2(x,y);
            adj[x].pb(y);
            adj[y].pb(x);
        }

        dep[1] = 0;
        dfs(1,1);

        RD(m);
        while(m--){
            RD2(x,y);
            printf("%d\n", solve(x,y) );
        }
    }

    return 0;
}
