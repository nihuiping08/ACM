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
inline void Char(char &x){
    while(!islower(x=getchar()));
}

/******** program ********************/

const int MAXN = 110005;

int st[MAXN],ed[MAXN],tim;
vector<int> adj[MAXN];

struct segTree{
    int l,r,mx;
    bool lz;
    inline int mid(){
        return (l+r)>>1;
    }
    inline int rev(){
        return r-l+1-mx;
    }
}tree[MAXN<<2];

void dfs(int x){
    st[x] = ++ tim;
    foreach(i,adj[x])
        dfs(adj[x][i]);
    ed[x] = tim;
}

void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    tree[rt].mx = 0;
    tree[rt].lz = 0;
    if(l==r)return;
    int mid = tree[rt].mid();
    build(l,mid,lson);
    build(mid+1,r,rson);
}

void push(int rt){
    if(tree[rt].lz){
        tree[lson].mx = tree[lson].rev();
        tree[lson].lz ^= 1;
        tree[rson].mx = tree[rson].rev();
        tree[rson].lz ^= 1;
        tree[rt].lz = 0;
    }
}

void modify(int l,int r,int rt){
    if(l<=tree[rt].l&&tree[rt].r<=r){
        tree[rt].mx = tree[rt].rev();
        tree[rt].lz ^= 1;
        return;
    }
    push(rt);
    int mid = tree[rt].mid();
    if(r<=mid)modify(l,r,lson);
    else if(l>mid)modify(l,r,rson);
    else{
        modify(l,r,lson);
        modify(l,r,rson);
    }
    tree[rt].mx = tree[lson].mx+tree[rson].mx;
}

int ask(int l,int r,int rt){
    if(l<=tree[rt].l&&tree[rt].r<=r)
        return tree[rt].mx;
    push(rt);
    int mid = tree[rt].mid();
    if(r<=mid)return ask(l,r,lson);
    else if(l>mid)return ask(l,r,rson);
    else return ask(l,r,lson)+ask(l,r,rson);
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int n,m,x;
    char op;
    while(~RD2(n,m)){
        rep1(i,n)
            adj[i].clear();
        REP(i,2,n){
            Int(x);
            adj[x].pb(i);
        }

        tim = 0;
        dfs(1);
        build(1,n,1);

        while(m--){
            Char(op);Int(x);
            if(op=='o')modify(st[x],ed[x],1);
            else printf("%d\n",ask(st[x],ed[x],1));
        }
        puts("");
    }

    return 0;
}
