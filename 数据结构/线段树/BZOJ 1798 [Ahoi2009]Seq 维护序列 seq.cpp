/*

题目:
    双标记，区间加和区间乘两个标记

分析：
    把区间加看作是*1+c，把区间乘看作是*c+0
    具体的看下沉标记以及上传操作

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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)

const int MAXN = 100005;

#define lx rt<<1
#define rx rt<<1|1

int a[MAXN];
ll MOD;
int n,m;

struct Seg_tree{
    int l,r;
    ll sum,mul,add;
    inline int mid(){
        return (l+r)>>1;
    }
}tree[MAXN<<2];

void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    tree[rt].mul = 1;
    tree[rt].add = 0;
    if(l==r){
        tree[rt].sum = a[l];
        return;
    }
    int mid = tree[rt].mid();
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
    tree[rt].sum = (tree[lx].sum+tree[rx].sum)%MOD;
}

void push_down(int rt){
    tree[lx].mul = (tree[rt].mul*tree[lx].mul)%MOD;
    tree[rx].mul = (tree[rt].mul*tree[rx].mul)%MOD;
    // 儿子结点加的标记需要乘以父节点的乘标记
    tree[lx].add = (tree[rt].mul*tree[lx].add+tree[rt].add)%MOD;
    tree[rx].add = (tree[rt].mul*tree[rx].add+tree[rt].add)%MOD;
    tree[rt].add = 0;
    tree[rt].mul = 1;
}

void push_up(int rt){
    int mid = tree[rt].mid();
    // 区间每个元素加上一个数，所以需要乘以区间的长度
    tree[rt].sum  = (tree[lx].sum*tree[lx].mul+tree[lx].add*(mid-tree[rt].l+1));
    tree[rt].sum += (tree[rx].sum*tree[rx].mul+tree[rx].add*(tree[rt].r-mid));// 右区间是(mid,r]
    tree[rt].sum %= MOD;
}

void modify(int l,int r,ll mul,ll add,int rt){
    if(l==tree[rt].l&&tree[rt].r==r){
        tree[rt].mul = (tree[rt].mul*mul)%MOD;
        tree[rt].add = (tree[rt].add*mul+add)%MOD;
        return;
    }
    push_down(rt);
    int mid = tree[rt].mid();
    if(r<=mid)
        modify(l,r,mul,add,lx);
    else if(l>mid)
        modify(l,r,mul,add,rx);
    else{
        modify(l,mid,mul,add,lx);
        modify(mid+1,r,mul,add,rx);
    }
    push_up(rt);
}

int ask(int l,int r,int rt){
    if(tree[rt].l==l&&r==tree[rt].r)
        return (tree[rt].sum*tree[rt].mul+tree[rt].add*(r-l+1))%MOD;
    push_down(rt);
    int mid = tree[rt].mid();
    push_up(rt);
    if(r<=mid)
        return ask(l,r,lx);
    if(l>mid)
        return ask(l,r,rx);
    return (ask(l,mid,lx)+ask(mid+1,r,rx))%MOD;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    cin>>n>>MOD;
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    build(1,n,1);

    RD(m);
    int x,y,z,op;
    while(m--){
        RD2(op,x);
        if(op==3){
            RD(y);
            printf("%d\n",ask(x,y,1));
        }else{
            RD2(y,z);
            if(op==1)   modify(x,y,z,0,1);
            else        modify(x,y,1,z,1);
        }
    }

	return 0;
}

