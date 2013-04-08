/*

題目：
    DP[i] = max(dp[j])+1, |num[i]-num[j]|<=m
分析:
    線段樹維護DP。
    對於每個num_i，二分出他是第x小，然後在線段樹x的位子上插入查詢到的
    該位置最優值。

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

#define lx(x) (x<<1)
#define rx(x) (x<<1|1)
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

const int MAXN = 100005;

int a[MAXN],b[MAXN],n,m;

struct Seg{
    int l,r,val;
    int mid(){
        return (l+r)>>1;
    }
}tree[MAXN<<2];

void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    tree[rt].val = 0;
    if(l==r)
        return;
    int mid = tree[rt].mid();
    build(l,mid,lx(rt));
    build(mid+1,r,rx(rt));
}

void modify(int pos,int val,int rt){
    if(tree[rt].l==tree[rt].r){
        tree[rt].val = max(tree[rt].val,val);
        return;
    }
    int mid = tree[rt].mid();
    if(pos<=mid)
        modify(pos,val,lx(rt));
    else
        modify(pos,val,rx(rt));
    tree[rt].val = max(tree[lx(rt)].val , tree[rx(rt)].val);
}

int ask(int l,int r,int rt){
    if(tree[rt].l==l&&tree[rt].r==r)
        return tree[rt].val;
    int mid = tree[rt].mid();
    if(r<=mid)
        return ask(l,r,lx(rt));
    else if(l>mid)
        return ask(l,r,rx(rt));
    else
        return max(ask(l,mid,lx(rt)),ask(mid+1,r,rx(rt)));
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD2(n,m)){
        rep(i,n){
            RD(a[i]);
            b[i] = a[i];
        }
        sort(b,b+n);
        int tot = unique(b,b+n)-b;

        build(0,tot,1);

        int ans = 0;
        rep(i,n){
            int l = lower_bound(b,b+tot,a[i]-m)-b;
            int r = upper_bound(b,b+tot,a[i]+m)-b-1;
            int x = ask(l,r,1)+1;
            ans = max(ans,x);
            int pos = lower_bound(b,b+tot,a[i])-b;
            modify(pos,x,1);
        }
        cout<<ans<<endl;
    }

	return 0;
}
