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

const int MAXN = 1e5+5;
const int LOG = 20;

struct node{
    int y,val,next;
}edge[MAXN];

int po[MAXN],tol;
int dis[MAXN],dep[MAXN];
int p[MAXN][22];

inline void add(int x,int y,int val){
    edge[++tol].y = y;
    edge[tol].val = val;
    edge[tol].next = po[x];
    po[x] = tol;
}

void dfs(int x,int fa,int depth,int cost){
    dis[x] = cost;
    dep[x] = depth;
    p[x][0] = fa;
    rep1(i,LOG)
        p[x][i] = p[ p[x][i-1] ][i-1];
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)continue;
        dfs(y,x,depth+1,cost+edge[i].val);
    }
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

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int m,n;
    while(~RD2(n,m)){
        int x,y,val;
        char op[2];

        Clear(po);
        tol = 1;

        REP(i,2,n){
            RD3(x,y,val);
            scanf("%s",op);
            add(x,y,val);
            add(y,x,val);
        }
        dfs(1,1,1,0);

        RD(m);
        while(m--){
            RD2(x,y);
            //cout<<"lca = "<<lca(x,y)<<endl;
            printf("%d\n",dis[x]+dis[y]-2*dis[lca(x,y)]);
        }
    }

    return 0;
}
