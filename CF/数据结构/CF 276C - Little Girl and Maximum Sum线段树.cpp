/*

线段树做法：区间更新，询问总区间就可以把所有的数存在数组中了

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

string str;

const int X = 2e5+5;

ll a[X];
int val[X];

struct node{
    int l,r;
    ll add;
    int mid(){
        return (l+r)>>1;
    }
}tree[X<<2];

void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    tree[rt].add = 0;
    if(l==r)
        return;
    int mid = (l+r)>>1;
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
}

void push_down(int rt){
    tree[rt<<1].add   += tree[rt].add;
    tree[rt<<1|1].add += tree[rt].add;
    tree[rt].add = 0;
}

void update(int l,int r,int rt){
    if(tree[rt].l==l&&tree[rt].r==r){
        tree[rt].add ++;
        return;
    }
    if(tree[rt].add)
        push_down(rt);
    int mid = tree[rt].mid();
    if(r<=mid)
        update(l,r,rt<<1);
    else if(l>mid)
        update(l,r,rt<<1|1);
    else
        update(l,mid,rt<<1),update(mid+1,r,rt<<1|1);
}

void query(int l,int r,int rt){
    if(tree[rt].l==tree[rt].r){
        a[l] = tree[rt].add;
        return;
    }
    if(tree[rt].add)
        push_down(rt);
    int mid = tree[rt].mid();
    if(l<=mid)
        query(tree[rt].l,mid,rt<<1);
    if(r>mid)
        query(mid+1,tree[rt].r,rt<<1|1);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif
    int n,m,x,y;
    while(cin>>n>>m){
        rep(i,n)
            scanf("%d",&val[i+1]);
        build(1,n,1);
        while(m--){
            scanf("%d%d",&x,&y);
            update(x,y,1);
        }
        query(1,n,1);
        sort(a+1,a+n+1);
        sort(val+1,val+n+1);
        ll ans = 0;
        rep(i,n)
            ans += a[i+1]*val[i+1];
        cout<<ans<<endl;
    }

	return 0;
}

