/*
给出一棵树，树的节点有权值，有两种操作：

1.询问节点x,y的路径上最大子段和，可以为空

2.把节点x,y的路径上所有节点的权值置为c

分析：

修改树路径的信息，可以考虑一下树链剖分、动态树。

 由于x,y可能不在同一个重链上，所以在询问时需要分两段进行统计，合并的时候跟GSS1基本一样。
 对于求完lca之后，我们可以注意一下两个链的合并方向。

建立lazy标记的时候，下沉时需要把子节点的值相应的更新，这时注意到可以为空，所以需要判断
值是否为负数。

其他的没什么了。
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

int son[MAXN],sz[MAXN],top[MAXN],fa[MAXN],tid[MAXN],dep[MAXN],tim;
bool use[MAXN];
int a[MAXN],in[MAXN];
int po[MAXN],tol;

struct Edge{
    int y,next;
}edge[MAXN<<1];

struct segTree{
    int l,r,lx,rx,mx,sum;
    int same;
    bool cov;

    segTree(){
        l = r = lx = rx = mx = sum = 0;
    }
    inline int mid(){
        return (l+r)>>1;
    }
    inline int dis(){
        return (r-l+1);
    }
}tree[MAXN<<2];

inline void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

// 树链剖分部分 ok
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

inline void update(segTree &now,segTree l,segTree r){
    now.sum = l.sum+r.sum;
    now.lx = max( l.lx , l.sum+r.lx );
    now.rx = max( r.rx , r.sum+l.rx );
    now.mx = max( l.rx+r.lx , max(l.mx,r.mx) );
    now.same = now.cov = 0;
}

void setc(segTree &now,int same){
    now.sum = now.dis()*same;
    now.lx = now.rx = now.mx = max(0,now.sum);
    now.cov = true;
    now.same = same;
}

inline void pushDown(int rt){
    if(tree[rt].cov==false)return;
    setc(tree[rt<<1],tree[rt].same);
    setc(tree[rt<<1|1],tree[rt].same);
    tree[rt].same = tree[rt].cov = 0;
}

void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    if(l==r){
        setc(tree[rt],a[l]);
        tree[rt].cov = 0;
        return;
    }
    int mid = tree[rt].mid();
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
    update(tree[rt],tree[rt<<1],tree[rt<<1|1]);
}

void modify(int l,int r,int c,int rt){
    if(l<=tree[rt].l&&tree[rt].r<=r){
        setc(tree[rt],c);
        return;
    }
    pushDown(rt);
    int mid = tree[rt].mid();
    if(r<=mid)modify(l,r,c,rt<<1);
    else if(l>mid)modify(l,r,c,rt<<1|1);
    else{
        modify(l,r,c,rt<<1);
        modify(l,r,c,rt<<1|1);
    }
    update(tree[rt],tree[rt<<1],tree[rt<<1|1]);
}

segTree ask(int l,int r,int rt){
    if(l<=tree[rt].l&&tree[rt].r<=r)
        return tree[rt];
    pushDown(rt);
    int mid = tree[rt].mid();
    segTree ans;
    if(r<=mid)ans = ask(l,r,rt<<1);
    else if(l>mid)ans = ask(l,r,rt<<1|1);
    else{
        segTree a = ask(l,r,rt<<1);
        segTree b = ask(l,r,rt<<1|1);
        update(ans,a,b);
    }
    update(tree[rt],tree[rt<<1],tree[rt<<1|1]);
    return ans;
}

inline void modify(int x,int y,int c){
    while(top[x]!=top[y]){
        if(dep[ top[x] ]<dep[ top[y] ])
            swap(x,y);
        modify(tid[top[x]],tid[x],c,1);
        x = fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    modify(tid[x],tid[y],c,1);
}

void out(segTree l){
    cout<<l.lx<<" "<<l.rx<<" "<<l.mx<<endl;
}

inline int ask(int x,int y){
    segTree l,r;
    while(top[x]!=top[y]){
        if(dep[top[x]]>=dep[top[y]]){
            segTree tmp = ask(tid[top[x]],tid[x],1);
            update(l,tmp,l);
            x = fa[top[x]];
        }else{
            segTree tmp = ask(tid[top[y]],tid[y],1);
            update(r,tmp,r);
            y = fa[top[y]];
        }
    }

    if(dep[x]>=dep[y]){
        segTree tmp = ask(tid[y],tid[x],1);
        update(l,tmp,l);
    }else{
        segTree tmp = ask(tid[x],tid[y],1);
        update(r,tmp,r);
    }
    return max( l.lx+r.lx,max(l.mx,r.mx) );
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int x,y,c,op,n,m;
    //int ncase = 0;
    while(~RD(n)){
        //ncase?puts("----------------------"):ncase = 1;
        rep1(i,n)
            RD(in[i]);

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
            a[ tid[i] ] = in[i];

        build(1,n,1);

        RD(m);
        while(m--){
            RD3(op,x,y);
            if(op==1){
                printf("%d\n",ask(x,y));
            }else{
                RD(c);
                modify(x,y,c);
            }
        }
    }
    return 0;
}
