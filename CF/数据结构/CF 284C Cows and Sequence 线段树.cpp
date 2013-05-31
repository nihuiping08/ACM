/*

题目：
	线段树区间操作

*/
#include <set>
#include <map>
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

/******** program ********************/

const int MAXN = 2e5+5;

struct node{
    int l,r;
    ll add,sum;
    int mid(){
        return (l+r)>>1;
    }
    ll cal(){
        return (r-l+1)*add+sum;
    }
}tree[MAXN<<2];

void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    tree[rt].add = tree[rt].sum = 0;
    if(l==r)return;
    int mid = (l+r)>>1;
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
}

void update(int rt){
    tree[rt<<1].add += tree[rt].add;
    tree[rt<<1|1].add += tree[rt].add;
    tree[rt].add = 0;
}

void push_up(int rt){
    tree[rt].sum = tree[rt<<1].cal()+tree[rt<<1|1].cal();
}

void modify(int l,int r,int val,int rt){
    if(tree[rt].l==l&&tree[rt].r==r){
        tree[rt].add += val;
        return;
    }
    update(rt);
    int mid = tree[rt].mid();
    if(r<=mid)
        modify(l,r,val,rt<<1);
    else if(l>mid)
        modify(l,r,val,rt<<1|1);
    else{
        modify(l,mid,val,rt<<1);
        modify(mid+1,r,val,rt<<1|1);
    }
    push_up(rt);
}

void del(int pos,int rt){
    if(tree[rt].l==tree[rt].r){
        tree[rt].sum = tree[rt].add = 0;
        return;
    }
    update(rt);
    int mid = tree[rt].mid();
    if(pos<=mid)    del(pos,rt<<1);
    else            del(pos,rt<<1|1);
    push_up(rt);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    while(~RD(ncase)){
        int op,x,y;
        build(1,ncase+5,1);
        int n = 1;
        while(ncase--){
            RD(op);
            if(op==1){
                RD2(x,y);
                modify(1,x,y,1);
            }else if(op==2){
                RD(x);
                ++ n;
                modify(n,n,x,1);
            }else{
                del(n,1);
                n --;
            }
            //cout<<tree[1].sum<<" ";
            printf("%lf\n",tree[1].sum*1.0/n);
        }
    }

	return 0;
}
