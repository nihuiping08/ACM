/*

 给出数列a1...an，询问时给出：

Query(x1,y1,x2,y2) = Max { A[i]+A[i+1]+...+A[j] ; x1 <= i <= y1 , x2 
	j <= y2 and x1 <= x2 , y1 <= y2 }

 

 

分析：

其实画个图分类讨论一下之后，跟gss1基本一样。。。

注意到x1<=x2 , y1<=y2.

所以大致可以分为：

1.y1<x2:

　　直接计算区间[x1,y1]的右子区间连续最大和，[x2,y2]的左区间连续最大和，如果y1与x2之间
	有空隙的话，需要加上[y1+1,x2-1]的和。

 
2.y2>=x2:

　　考虑x1与x2的关系：

	如果x1==x2，最大值可能出现在区间[x1,y1]的最大子段和，[x1,y1]的右区间连续最
	大和加上[y1+1,y2]的左区间连续最大和。
	否则，考虑三个区间[x1,x2-1],[x2,y1],[y1+1,y2]，这时考虑方式跟上面差不多，
	就不写出来了，具体可以看代码。

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

const int MAXN = 100005;

int a[MAXN];

struct segTree{
    int l,r,lx,rx,mx,sum;
    inline int mid(){
        return (l+r)>>1;
    }
}tree[MAXN<<2];

inline void Union(segTree& now,segTree l,segTree r){
    now.lx = max( l.lx , l.sum+max(0,r.lx) );
    now.rx = max( r.rx , r.sum+max(0,l.rx) );
    now.mx = max( l.rx+r.lx , max(l.mx,r.mx) );
    now.sum = l.sum+r.sum;
}

void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    if(l==r){
        tree[rt].lx = tree[rt].rx = tree[rt].sum = tree[rt].mx = a[l];
        return;
    }
    int mid = tree[rt].mid();
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
    Union(tree[rt],tree[rt<<1],tree[rt<<1|1]);
}

void modify(int pos,int c,int rt){
    if(tree[rt].l==tree[rt].r){
        tree[rt].lx = tree[rt].rx = tree[rt].mx = tree[rt].sum = c;
        return;
    }
    int mid = tree[rt].mid();
    if(pos<=mid)modify(pos,c,rt<<1);
    else        modify(pos,c,rt<<1|1);
    Union(tree[rt],tree[rt<<1],tree[rt<<1|1]);
}

segTree ask(int l,int r,int rt){
    if(l<=tree[rt].l&&r>=tree[rt].r)
        return tree[rt];
    int mid = tree[rt].mid();
    segTree ans;
    if(r<=mid)      ans = ask(l,r,rt<<1);
    else if(l>mid)  ans = ask(l,r,rt<<1|1);
    else{
        segTree a = ask(l,r,rt<<1);
        segTree b = ask(l,r,rt<<1|1);
        Union( ans,a,b );
    }
    Union(tree[rt],tree[rt<<1],tree[rt<<1|1]);
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int m,n,x,y,c,d;
    int ncase;
    RD(ncase);
    while(ncase--){
        RD(n);
        rep1(i,n)
            RD(a[i]);
        build(1,n,1);
        RD(m);
        segTree ca,cb,cc;
        while(m--){
            RD4(x,y,c,d);
            int sum = 0;
            if(y>=c){
                if(x<c){
                    ca = ask(x,c-1,1);
                    cb = ask(c,y,1);
                    sum = max( ca.rx+cb.lx,cb.mx );
                    if(y<d){
                        cc = ask(y+1,d,1);
                        int tmp = max( max(0,ca.rx)+cb.sum+cc.lx , cb.rx+cc.lx );
                        sum = max( sum,tmp );
                    }
                }else{
                    ca = ask(c,y,1);
                    sum = ca.mx;
                    if(y<d){
                        cc = ask(y+1,d,1);
                        sum = max(sum,ca.rx+cc.lx);
                    }
                }
            }else{
                ca = ask(x,y,1);
                cb = ask(c,d,1);
                sum = ca.rx+cb.lx;
                if(y+1<c){
                    cc = ask(y+1,c-1,1);
                    sum += cc.sum;
                }
            }
            printf("%d\n",sum);
        }
    }

    return 0;
}

