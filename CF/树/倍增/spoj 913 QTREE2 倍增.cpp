/*
题目：

给出一棵树，求：
1.两点之间距离。
2.从节点x到节点y最短路径上第k个节点的编号。

 
分析：
　　第一问的话，随便以一个节点为根，求得其他节点到根的距离，然后对于每个询问(x,y)，
	想求得lca(x,y)，直接用dis[x]+dis[y]-2*dis[ lca(x,y) ]即可。
　　第二问的话，可以用倍增的方式求。我们通过求得节点x,y,lca(x,y)的深度，判断第k个
	节点落在哪个链上，该链是指是从x到根或者从y到根。最后倍增可以轻松求出一个链上第k个
	父亲是谁了。

　　我实现的时候，lca以及求某个节点的第k个祖先都是用倍增的思想实现。
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
 
const int MAXN = 1e5+5;
const int LOG = 20;
 
struct node{
    int y,val,next;
}edge[MAXN];
 
int dis[MAXN];
int po[MAXN],tol;
int dep[MAXN];
int p[MAXN][22];
 
inline void add(int x,int y,int val){
    edge[++tol].y = y;
    edge[tol].val = val;
    edge[tol].next = po[x];
    po[x] = tol;
}
 
void dfs(int x,int fa,int depth,int cost){
    dep[x] = depth;
    p[x][0] = fa;
    dis[x] = cost;
 
    rep1(i,LOG)
        p[x][i] = p[ p[x][i-1] ][i-1]; // 倍增，可以画个树理解一下，存的是节点x第2^i个祖先
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)continue;
        dfs(y,x,depth+1,cost+edge[i].val);
    }
}
 
int lca(int x,int y){ // 倍增求lca
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
 
int cc(int x,int k){ // 求节点x的第k个祖先编号
    for(int i=0;i<LOG;i++)
        if( k>>i & 1 )
            x = p[x][i];
    return x;
}
 
int cc(int k,int x,int y){ // 求x到y路径上第k节点编号
    int ca = lca(x,y);
    if(dep[x]-dep[ca]+1>=k){
        return cc(x,k-1);
    }else{
        k -= dep[x]-dep[ca];
        k = dep[y]-dep[ca]-k+1;
        return cc(y,k);
    }
}
 
int main(){
 
#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif
 
    int n,ncase,x,y,k;
    RD(ncase);
    char op[10];
 
    while(ncase--){
        Clear(po);
        tol = 0;
 
        RD(n);
        REP(i,2,n){
            RD3(x,y,k);
            add(x,y,k);
            add(y,x,k);
        }
 
        dfs(1,1,1,0);
 
        while(scanf("%s",op),op[1]!='O'){
            if(op[1]=='I'){
                RD2(x,y);
                printf("%d\n",dis[x]+dis[y]-2*dis[lca(x,y)]);
            }else{
                RD3(x,y,k);
                printf("%d\n",cc(k,x,y));
            }
        }
    }
 
    return 0;
}