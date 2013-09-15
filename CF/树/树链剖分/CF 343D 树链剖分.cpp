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

const int MAXN = 500005;

int son[MAXN],sz[MAXN],dep[MAXN],fa[MAXN],top[MAXN],tim;
bool use[MAXN];
int st[MAXN],ed[MAXN];
int po[MAXN],tol;
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
    ed[x] = tim;
}

// 线段树部分
struct segTree{
    int l,r;
    int col,lz;
    inline int mid(){
        return (l+r)>>1;
    }
}tree[MAXN<<2];

inline void push(int rt){
    if(tree[rt].lz){
        tree[rt<<1].lz = tree[rt<<1|1].lz = 1;
        tree[rt<<1].col = tree[rt<<1|1].col = tree[rt].col;
        tree[rt].lz = 0;
    }
}

void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    tree[rt].col = 0;
    tree[rt].lz = 0;
    if(l==r)return;
    int mid = tree[rt].mid();
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
}

void modify(int l,int r,bool col,int rt){
    if(l<=tree[rt].l&&tree[rt].r<=r){
        tree[rt].lz = true;
        tree[rt].col = col;
        return;
    }
    push(rt);
    int mid = tree[rt].mid();
    if(r<=mid)modify(l,r,col,rt<<1);
    else if(l>mid)modify(l,r,col,rt<<1|1);
    else{
        modify(l,r,col,rt<<1);
        modify(l,r,col,rt<<1|1);
    }
}

int ask(int pos,int rt){
    if(tree[rt].l==tree[rt].r)
        return tree[rt].col;
    push(rt);
    int mid = tree[rt].mid();
    if(pos<=mid)return ask(pos,rt<<1);
    else return ask(pos,rt<<1|1);
}

inline void lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        modify( st[top[x]],st[x],0,1 );
        x = fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    modify(st[x],st[y],0,1);
}


int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int n,m,x,y;
    cin>>n;
    REP(i,2,n){
        RD2(x,y);
        add(x,y);
        add(y,x);
    }

    dfsFind(1,1,1);
    Clear(use);
    tim = 0;
    dfsCon(1,1);

    build(1,n,1);

    RD(m);
    while(m--){
        RD2(y,x);
        if(y==1)
            modify( st[x],ed[x],1,1 );
        else if(y==2)
            lca(1,x);
        else
            printf("%d\n",ask(st[x],1));
    }

    return 0;
}
