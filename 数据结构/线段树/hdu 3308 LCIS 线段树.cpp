#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

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
    while(!isupper(x=getchar()));
}

/******** program ********************/

const int MAXN = 200105;

int son[MAXN],sz[MAXN],top[MAXN],fa[MAXN],tid[MAXN],dep[MAXN],tim;
bool use[MAXN];
int a[MAXN];

struct segTree{
    int l,r;
    int lval,rval;
    int lix,mix;
    int rdx;
    segTree(){
        l = r = lval = rval = 0;
        lix = mix = 0;
        rdx = 0;
    }
    inline int mid(){
        return (l+r)>>1;
    }
    inline int dis(){
        return r-l+1;
    }
}tree[MAXN<<1];

inline void update(segTree &now,segTree l,segTree r){
    // lix
    if(l.lix==l.dis()&&l.rval<r.lval)
        now.lix = l.lix+r.lix;
    else now.lix = l.lix;

    // mix
    if(l.rval<r.lval)
        now.mix = max(max(l.mix,r.mix),l.rdx+r.lix);
    else now.mix = max(l.mix,r.mix);

    // rdx
    if(r.dis()==r.rdx&&r.lval>l.rval)
        now.rdx = r.rdx+l.rdx;
    else now.rdx = r.rdx;

    now.lval = l.lval;
    now.rval = r.rval;
}

void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    if(l==r){
        tree[rt].lval = tree[rt].rval = a[l];
        tree[rt].lix = tree[rt].mix = 1;
        tree[rt].rdx = 1;
        return;
    }
    int mid = tree[rt].mid();
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
    update(tree[rt],tree[rt<<1],tree[rt<<1|1]);
}

void modify(int pos,int val,int rt){
    if(tree[rt].l==tree[rt].r){
        tree[rt].lval = tree[rt].rval = val;
        return;
    }
    int mid = tree[rt].mid();
    if(pos<=mid)modify(pos,val,rt<<1);
    else modify(pos,val,rt<<1|1);
    update(tree[rt],tree[rt<<1],tree[rt<<1|1]);
}

segTree ask(int l,int r,int rt){
    if(l<=tree[rt].l&&tree[rt].r<=r)
        return tree[rt];
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

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    char op;
    int n,m,ncase,x,y;
    Int(ncase);
    while(ncase--){
        Int(n);Int(m);
        for(int i=1;i<=n;i++)
            Int(a[i]);
        build(1,n,1);
        while(m--){
            Char(op);
            Int(x);Int(y);
            if(op=='Q')printf("%d\n",ask(++x,++y,1).mix);
            else modify(++x,y,1);
        }
    }

    return 0;
}
