/*

 给出一棵树，树节点的颜色初始时为白色，有两种操作：

0.把节点x的颜色置反（黑变白，白变黑）。

1.询问节点1到节点x的路径上第一个黑色节点的编号。

 

分析：

先树链剖分，线段树节点维护深度最浅的节点编号。

注意到，如果以节点1为树根时，显然每条重链在一个区间，并且区间的左端会出现在深度浅的地方。
所以每次查找时发现左区间有的话，直接更新答案。

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

const int MAXN = 200005;

int son[MAXN],tid[MAXN],top[MAXN],dep[MAXN],fa[MAXN],sz[MAXN],tim;
bool use[MAXN];
int id[MAXN];
int po[MAXN],tol;

struct segTree{
    int l,r,pos,c;
    inline int mid(){
        return (l+r)>>1;
    }
}tree[MAXN<<2];

struct Edge{
    int y,next;
}edge[MAXN<<1];

inline void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

// 树链剖分部分
void dfsFind(int x,int pa,int depth){
    dep[x] = depth;
    fa[x] = pa;
    sz[x] = 1;
    son[x] = 0;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==pa)continue;
        dfsFind(y,x,depth+1);
        sz[x] += sz[y];
        if(sz[y]>sz[ son[x] ])
            son[x] = y;
    }
}

void dfsCon(int x,int pa){
    use[x] = true;
    top[x] = pa;
    tid[x] = ++ tim;
    if(son[x])dfsCon(son[x],pa);
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(use[y])continue;
        dfsCon(y,y);
    }
}

void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    tree[rt].pos = 0;
    tree[rt].c = 0;
    if(l==r) return;
    int mid = tree[rt].mid();
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
}

void modify(int pos,int rt){
    if(tree[rt].l==tree[rt].r){
        tree[rt].c ^= 1;
        if(tree[rt].c)  tree[rt].pos = id[tree[rt].l];
        else            tree[rt].pos = 0;
        return;
    }
    int mid = tree[rt].mid();
    if(pos<=mid)modify(pos,rt<<1);
    else        modify(pos,rt<<1|1);

    if(tree[rt<<1].c){
        tree[rt].c = tree[rt<<1].c;
        tree[rt].pos = tree[rt<<1].pos;
    }else{
        tree[rt].c = tree[rt<<1|1].c;
        tree[rt].pos = tree[rt<<1|1].pos;
    }
}

int ask(int l,int r,int rt){
    if(tree[rt].c==0)return 0;
    if(l<=tree[rt].l&&tree[rt].r<=r)
        return tree[rt].pos;
    int mid = tree[rt].mid();
    if(r<=mid)return ask(l,r,rt<<1);
    else if(l>mid)return ask(l,r,rt<<1|1);
    else{
        int t = ask(l,r,rt<<1);
        if(t)return t;
        return ask(l,r,rt<<1|1);
    }
}

inline int ask(int y){
    int x = 1;
    int ans = -1;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        int t = ask(tid[top[x]],tid[x],1);
        if(t)ans = t;
        x = fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    int t = ask(tid[x],tid[y],1);
    if(t)ans = t;
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int x,y,n,q,op;
    while(~RD2(n,q)){
        Clear(po);
        tol = 0;
        REP(i,2,n){
            RD2(x,y);
            add(x,y);
            add(y,x);
        }

        dfsFind(1,1,1);
        tim = 0;
        Clear(use);
        dfsCon(1,1);
        rep1(i,n)
            id[ tid[i] ] = i;

        build(1,n,1);

        while(q--){
            RD2(op,x);
            if(op==0)   modify(tid[x],1);
            else        printf("%d\n",ask(x));
        }
    }

    return 0;
}
