/*

题目：给出一个数列，原数列和值不超过1e18，有两种操作：

0 x y：修改区间[x,y]所有数开方后向下调整至最近的整数

1 x y：询问区间[x,y]的和

 

分析：

　　昨天初看时没什么想法，于是留了个坑。终于在今天补上了。

　　既然给出了1e18这个条件，那么有什么用呢？于是想到了今年多校一题线段树区间操作时，
	根据一些性质能直接下沉到每个节点，这里可以吗？考虑1e18开方6次就下降到1了，因此每个
	节点最多被修改6次。于是我们每个节点（区间）记录一个该区间的最大值，每次修改时，先
	判断该区间是否最大的数已经等于1，等于的话，就不用继续往下修改了。不然的话，继续往下
	下沉。下沉到最终的区间时发现最大的数还大于1时，进行单点修改操作。在单点修改时同样如
	此判断。修改后update一下sum以及最大值就行。
	
*/
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

const int MAXN = 1e5+5;

ll a[MAXN];

struct segTree{
    int l,r;
    ll mx,sum;
    inline int mid(){
        return (l+r)>>1;
    }
}tree[MAXN<<2];

inline void update(int rt){
    tree[rt].mx = max(tree[rt<<1].mx,tree[rt<<1|1].mx);
    tree[rt].sum = tree[rt<<1].sum+tree[rt<<1|1].sum;
}

void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    if(l==r){
        tree[rt].sum = tree[rt].mx = a[l];
        return;
    }
    int mid = tree[rt].mid();
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
    update(rt);
}

void modify(int rt){
    if(tree[rt].mx==1LL)return;
    if(tree[rt].l==tree[rt].r){
        tree[rt].sum = tree[rt].mx = ll( sqrt(tree[rt].mx+0.0) );
        return;
    }
    modify(rt<<1);
    modify(rt<<1|1);
    update(rt);
}

void modify(int l,int r,int rt){
    if(tree[rt].mx==1LL)return;
    if(l<=tree[rt].l&&tree[rt].r<=r){
        modify(rt);
        return;
    }
    int mid = tree[rt].mid();
    if(r<=mid)      modify(l,r,rt<<1);
    else if(l>mid)  modify(l,r,rt<<1|1);
    else{
        modify(l,r,rt<<1);
        modify(l,r,rt<<1|1);
    }
    update(rt);
}

ll ask(int l,int r,int rt){
    if(l<=tree[rt].l&&tree[rt].r<=r)
        return tree[rt].sum;
    int mid = tree[rt].mid();
    if(r<=mid)      return ask(l,r,rt<<1);
    else if(l>mid)  return ask(l,r,rt<<1|1);
    else return ask(l,r,rt<<1) + ask(l,r,rt<<1|1);
}

inline void LL(ll &x){
    x = 0;
    char ch;
    while(isdigit(ch=getchar())==0);
    x = ch-'0';
    while(isdigit(ch=getchar()))
        x = x*10+ch-'0';
}

inline void Int(int &x){
    x = 0;
    char ch;
    while(isdigit(ch=getchar())==0);
    x = ch-'0';
    while(isdigit(ch=getchar()))
        x = x*10+ch-'0';
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int n,m,op,x,y;
    int ncase = 0;
    while(cin>>n){
        rep1(i,n){
            //scanf("%lld\n",&a[i]);
            LL(a[i]);
        }
        build(1,n,1);
        RD(m);
        printf("Case #%d:\n",++ncase);
        while(m--){
            //RD3(op,x,y);
            Int(op); Int(x); Int(y);
            if(x>y)swap(x,y);
            if(op)  printf("%lld\n",ask(x,y,1));
            else    modify(x,y,1);
        }
        puts("");
    }

    return 0;
}
