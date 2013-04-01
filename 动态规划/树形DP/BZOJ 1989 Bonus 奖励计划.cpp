/*

題目：
    隨機獎勵樹上的一條路徑，然後問國王需要付的費用

分析：
    樹上的路徑數目為c(n,2)
    然後我們知道穿過該條路徑的概率為通過該點的路徑數除以總路徑數的平方。

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
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

/******** program ********************/

const int MAXN = 10005;

int sz[MAXN],a[MAXN];
int po[MAXN],tol,n;
double ans;

struct node{
    int y,next;
}edge[2*MAXN];

void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

ll sqr(ll x){
    return x*x;
}

void dfs(int x,int fa){
    sz[x] = 1;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)
            continue;
        dfs(y,x);
        sz[x] += sz[y];
    }
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)
            continue;
        ans += sqr(sz[y]*(n-sz[y]));
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int x,y;
    while(~RD(n)){
        memset(po,0,sizeof(po));
        tol = 0;
        REP(i,2,n){
            RD2(x,y);
            add(x,y);
            add(y,x);
        }
        memset(sz,0,sizeof(sz));
        ans = 0;
        dfs(1,0);
        ll m = n*(n-1)>>1;
        printf("%.6lf\n",ans/m/m);
    }

	return 0;
}
