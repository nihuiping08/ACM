/*

给出n个串，问最多能够选出多少个串，使得前面串是后面串的子串（按照输入顺序）

建立所有单词的AC自动机，对于每个节点的转移，都是从parent[]或者从fail[]，
fail[fail[]]，...得到的。可以看出fail[]的关系形成一棵树，于是问题转化成，
不断在节点处插入，询问点到根路径上的最大值，可以利用dfs序列转化用线段树维护。

*/
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <complex>
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
#define SZ(x) x.size()

/******** program ********************/

const int MAXN = 3e5+5;
const int kind = 26;

char s[MAXN];
int beg[MAXN];

struct segTree {
    int l,r,mx;
    int cov;
    inline int mid() {
        return (l+r)>>1;
    }
} tree[MAXN<<2];

void build(int l,int r,int rt) {
    tree[rt].l = l;
    tree[rt].r = r;
    tree[rt].cov = tree[rt].mx = 0;
    if(l==r)return;
    int mid = tree[rt].mid();
    build(l,mid,lson);
    build(mid+1,r,rson);
}

void update(int rt){
    if(tree[rt].cov==0)return;
    cmax( tree[lson].cov,tree[rt].cov );
    cmax( tree[rson].cov,tree[rt].cov );
    cmax( tree[lson].mx,tree[rt].cov );
    cmax( tree[rson].mx,tree[rt].cov );
    tree[rt].cov = 0;
}

void modify(int l,int r,int mx,int rt) {
    if(l<=tree[rt].l&&tree[rt].r<=r) {
        cmax(tree[rt].mx,mx);
        cmax(tree[rt].cov,mx);
        return;
    }
    update(rt);
    int mid = tree[rt].mid();
    if(r<=mid)modify(l,r,mx,lson);
    else if(l>mid)modify(l,r,mx,rson);
    else {
        modify(l,r,mx,lson);
        modify(l,r,mx,rson);
    }
    tree[rt].mx = max( tree[lson].mx,tree[rson].mx );
}

int ask(int pos,int rt) {
    if(tree[rt].l==tree[rt].r)
        return tree[rt].mx;
    update(rt);
    int mid = tree[rt].mid();
    if(pos<=mid)return ask(pos,lson);
    else return ask(pos,rson);
}

int ch[MAXN][kind],fail[MAXN];
int val[MAXN];
int st[MAXN],ed[MAXN];
int tot,tim;
vector<int> adj[MAXN];

inline void set(int x) {
    Clear(ch[x]);
    fail[x] = 0;
    adj[x].clear();
}
inline void init() {
    set(1);
    tot = 1;
}
inline int newNode() {
    set(++tot);
    return tot;
}
inline int ind(char c) {
    return c-'a';
}

inline void ins(int x,int y,int val) {
    int r = 1;
    REP(i,x,y) {
        int c = ind(s[i]);
        if(ch[r][c]==0)
            ch[r][c] = newNode();
        r = ch[r][c];
    }
}

inline void build() {
    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        int r = q.front();
        q.pop();
        if(fail[r])
            adj[ fail[r] ].pb(r);
        rep(c,kind) {
            int x = ch[r][c];
            if(!x)continue;
            q.push(x);

            int y = fail[r];
            while(y&&ch[y][c]==0)
                y = fail[y];
            fail[x] = y?ch[y][c]:1;
        }
    }
}

void dfs(int x) {
    st[x] = ++ tim;
    foreach(i,adj[x]) {
        int y = adj[x][i];
        dfs(y);
    }
    ed[x] = tim;
}

inline int run() {
    init();

    int n;
    RD(n);
    rep1(i,n) {
        scanf("%s",s+beg[i-1]);
        RD(val[i]);
        beg[i] = beg[i-1]+strlen(s+beg[i-1]);
        ins(beg[i-1],beg[i]-1,val[i]);
    }
    build();

    tim = 0;
    dfs(1);
    build(1,tim,1);

    int ans = 0;
    rep1(i,n) {
        int r = 1;
        int now = 0;
        for(int j=beg[i-1]; j<beg[i]; j++) {
            int c = ind(s[j]);
            r = ch[r][c];
            cmax(now,ask( st[r],1 ));
        }
        now += val[i];
        modify(st[r],ed[r],now,1);
        cmax(ans,now);
    }
    return ans;
}

int main() {

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int ssize = 128 << 20; // 256MB
    char *ppp = (char*)malloc(ssize) + ssize;
    __asm__("movl %0, %%esp\n" :: "r"(ppp) );

    int ncase,Ncase = 0;
    RD(ncase);
    while(ncase--)
        printf("Case #%d: %d\n",++Ncase,run());

    return 0;
}
