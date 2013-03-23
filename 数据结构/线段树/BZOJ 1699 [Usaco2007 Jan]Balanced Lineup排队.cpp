/*

题目：区间最大最小值查询
分析：线段树区间操作。

*/
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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

const int MAXN = 100005;

int a[MAXN],n,m;
int ans_max,ans_min;

struct node{
    int l,r,Max,Min;
    int mid(){
        return (l+r)>>1;
    }
}tree[MAXN<<2];

void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    if(l==r){
        tree[rt].Min = tree[rt].Max = a[l];
        return;
    }
    int mid = tree[rt].mid();
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
    tree[rt].Max = max(tree[rt<<1].Max,tree[rt<<1|1].Max);
    tree[rt].Min = min(tree[rt<<1].Min,tree[rt<<1|1].Min);
}

void ask(int l,int r,int rt){
    if(tree[rt].l==l&&tree[rt].r==r){
        ans_max = max(ans_max,tree[rt].Max);
        ans_min = min(ans_min,tree[rt].Min);
        return;
    }
    int mid = tree[rt].mid();
    if(r<=mid)
        ask(l,r,rt<<1);
    else if(l>mid)
        ask(l,r,rt<<1|1);
    else{
        ask(l,mid,rt<<1);
        ask(mid+1,r,rt<<1|1);
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD2(n,m);
    rep1(i,n)
        RD(a[i]);
    build(1,n,1);
    int x,y;
    while(m--){
        RD2(x,y);
        if(x==y){
            puts("0");
            continue;
        }
        ans_min = 100000000;
        ans_max = -1;
        if(x>y)
            swap(x,y);
        ask(x,y,1);
        printf("%d\n",ans_max-ans_min);
    }

	return 0;
}
