/*

分析：

　　考虑到询问的是子树的最小点权值，我们想到用dfs序维护，对于树链上的操作却无能为力。而树链上的操作可以用树链剖分，但是对于子树信息的维护却无能为力了。

 

　　所以我们可以先进行树链剖分，剖分完了之后，由于需要维护子树的信息，所以计算dfs序时跟树链剖分一样，先访问完重链，然后再访问轻链上的节点，标记dfs序。

　　对于换根操作怎么办？

　　换根操作其实只与询问操作相关。假设当前节点为x，根为root，如果x==root，直接询问整棵线段树。

　　否则，我们先倍增求lca(x,root)。（我们使用下图说明）。如果不等的话，其实根在x的上方，跟普通的树链剖分的新型lca求法一样求得答案。

　　如果lca等于x的话，即root = C，x = A。这时以x为根的子树其实就是整棵树不包含以节点B（实际上的根最靠近节点x的祖先）为根的子树的部分。对应的dfs序就是[ 1,st[b]-1 ] , [ ed[b]+1,2*n ]。所以我们先求得root的第dep[root]-dep[x]-1个祖先是谁y，然后用整个区间减掉y所对应的区间，就是询问的区间。

　　这是，进入某个节点的时间戳其实就是一个连续的区间。为了方便，出去时的时间戳在线段树中需要置为-1，更新时直接忽略他。

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

char op,s[12];
int tp;
inline void Int(int &x){
    while( !isdigit(op=getchar()) );
    x = op-'0';
    while( isdigit(op=getchar()) )
        x = x*10+op-'0';
}
inline void LL(ll &x){
    while( !isdigit(op=getchar()) );
    x = op-'0';
    while( isdigit(op=getchar()) )
        x = x*10+op-'0';
}
inline void Out(ll x){
    s[0] = '0';
    tp = 0;
    while(x){
        s[tp++] = x%10+'0';
        x /= 10;
    }
    for(int i=tp-1;i>=0;i--)
        putchar(s[i]);
    puts("");
}

const int MAXN = 200005;
const int LOG = 17;
const ll INF = 1e15;

int p[MAXN][18];
int son[MAXN],sz[MAXN],dep[MAXN],fa[MAXN],top[MAXN],tim;
bool use[MAXN];
int st[MAXN],ed[MAXN];
int po[MAXN],tol;
ll def[MAXN],val[MAXN];
int n,m;

struct Edge{
    int y,next;
}edge[MAXN<<1];

inline void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

// 树链剖分
void dfsFind(int x,int pa,int depth){
    p[x][0] = pa;
    rep1(i,LOG)
        p[x][i] = p[ p[x][i-1] ][i-1];

    son[x] = 0;
    sz[x] = 1;
    dep[x] = depth;
    fa[x] = pa;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==pa)continue;
        dfsFind(y,x,depth+1);
        sz[x] += sz[y];
        if(sz[y]>sz[son[x]])
            son[x] = y;
    }
}

void dfsCon(int x,int pa){
    use[x] = true;
    top[x] = pa;
    st[x] = ++ tim; // 记录进入时的时间戳
    if(son[x])dfsCon(son[x],pa);
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(!use[y])dfsCon(y,y);
    }
    ed[x] = ++ tim; // 记录出去时的时间戳
}

// 倍增部分
inline int kth(int x,int k){ // 第k个祖先
    rep(i,LOG)
        if( k>>i & 1 )
            x = p[x][i];
    return x;
}

inline int lca(int x,int y){
    if(dep[x]>dep[y])swap(x,y);
    if(dep[x]<dep[y]){
        int del = dep[y]-dep[x];
        rep(i,LOG)
            if( del>>i & 1 )
                y = p[y][i];
    }
    if(x!=y){
        for(int i=LOG-1;i>=0;i--)
            if(p[x][i]!=p[y][i])
                x = p[x][i] , y = p[y][i];
        x = p[x][0] , y = p[y][0];
    }
    return x;
}

// 线段树部分
struct segTree{
    int l,r;
    ll mx,lz;
    inline int mid(){
        return (l+r)>>1;
    }
    void out(){
        cout<<l<<" "<<r<<" "<<mx<<" "<<lz<<endl;
    }
}tree[MAXN<<2];

inline void push(int rt){
    if(tree[rt].lz){
        tree[rt].mx = tree[rt].lz;
        tree[rt<<1].lz = tree[rt].lz;
        tree[rt<<1].mx = tree[rt].lz;
        tree[rt<<1|1].lz = tree[rt].lz;
        tree[rt<<1|1].mx = tree[rt].lz;
        tree[rt].lz = 0;
    }
}

inline void update(segTree &now,segTree l,segTree r){
    if( ~l.mx ){
        if(~r.mx)now.mx = min(l.mx,r.mx);
        else now.mx = l.mx;
    }else if(~r.mx)now.mx = r.mx;
    else now.mx = INF;
}

void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    tree[rt].lz = 0;
    tree[rt].mx = INF;
    if(l==r)return;
    int mid = tree[rt].mid();
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
    //update(tree[rt],tree[rt<<1],tree[rt<<1|1]);
}

void modify(int l,int r,ll c,int rt){
    if(l<=tree[rt].l&&tree[rt].r<=r){
        tree[rt].lz = tree[rt].mx = c;
        return;
    }
    push(rt);
    int mid = tree[rt].mid();
    if(r<=mid)modify(l,r,c,rt<<1);
    else if(l>mid)modify(l,r,c,rt<<1|1);
    else{
        modify(l,r,c,rt<<1);
        modify(l,r,c,rt<<1|1);
    }
    update(tree[rt],tree[rt<<1],tree[rt<<1|1]);
}

ll ask(int l,int r,int rt){
    if(l<=tree[rt].l&&tree[rt].r<=r){
        if(~tree[rt].mx)
            return tree[rt].mx;
        return INF;
    }
    push(rt);
    int mid = tree[rt].mid();
    ll ans;
    if(r<=mid)ans = ask(l,r,rt<<1);
    else if(l>mid)ans = ask(l,r,rt<<1|1);
    else
        ans = min(ask(l,r,rt<<1),ask(l,r,rt<<1|1));
    update(tree[rt],tree[rt<<1],tree[rt<<1|1]);
    return ans;
}


// 修改时修改的节点均为进入节点时的时间戳
inline void modify(int x,int y,int w){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        modify( st[top[x]],st[x],w,1 );
        x = fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    modify(st[x],st[y],w,1);
}

int root;
inline ll ask(int x){
    if(x==root)return ask(1,n*2,1);
    int ca = lca(x,root);
    if(ca!=x)return ask(st[x],ed[x],1);

    int y; // 根最靠近x的祖先
    if(fa[root]==x)y = root;
    else y = kth(root,dep[root]-dep[x]-1);

    ll ans = INF; // 去掉某个区间就是询问的区间
    if(1<=st[y]-1)ans = min(ans,ask(1,st[y]-1,1));
    if(2*n>=ed[y]+1)ans = min(ans,ask(ed[y]+1,2*n,1));
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int x,y,op;
    ll w;
    while(~RD2(n,m)){
        Clear(po);
        tol = 0;

        REP(i,2,n){
            Int(x);Int(y);
            add(x,y);
            add(y,x);
        }
        rep1(i,n)
            LL(def[i]);
        Int(root);

        // 树链剖分
        dfsFind(1,1,1);

        Clear(use);
        tim = 0;
        dfsCon(1,1);

        // 建树
        build(1,2*n,1);
        rep1(i,n)
            modify(st[i],st[i],def[i],1);
        rep1(i,n)
            modify(ed[i],ed[i],-1,1); // 出去时的时间戳

        while(m--){
            Int(op);
            if(op==1)Int(root);
            else if(op==2){
                Int(x);Int(y);LL(w);
                modify(x,y,w);
            }else{
                Int(x);
                Out(ask(x));
            }
        }
    }

    return 0;
}
