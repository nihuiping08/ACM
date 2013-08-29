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

const int MAXN = 2e5+5;

struct segTree{
    int l,r,val;
    inline int mid(){
        return (l+r)>>1;
    }
}tree[MAXN<<2];
int a[MAXN];

void update(int rt,int ok){
    if(ok)
        tree[rt].val = tree[rt<<1].val | tree[rt<<1|1].val;
    else
        tree[rt].val = tree[rt<<1].val ^ tree[rt<<1|1].val;
}

void build(int l,int r,int rt,int ok){
    tree[rt].l = l;
    tree[rt].r = r;
    if(l==r){
        tree[rt].val = a[l];
        return;
    }
    int mid = tree[rt].mid();
    build(l,mid,rt<<1,ok^1);
    build(mid+1,r,rt<<1|1,ok^1);

    update(rt,ok);
}

void modify(int pos,int c,int rt,int ok){
    if(tree[rt].l==tree[rt].r){
        tree[rt].val = c;
        return;
    }
    int mid = tree[rt].mid();
    if(pos<=mid)modify(pos,c,rt<<1,ok^1);
    else        modify(pos,c,rt<<1|1,ok^1);
    update(rt,ok);
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int n,m,t;
    while(cin>>t>>m){
        n = 1<<t;
        rep1(i,n)
            RD(a[i]);
        build(1,n,1,t&1);
        int p,x;
        while(m--){
            RD2(p,x);
            modify(p,x,1,t&1);
            printf("%d\n",tree[1].val);
        }
    }

    return 0;
}
