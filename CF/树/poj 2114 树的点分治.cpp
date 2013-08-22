/*

题目：寻找距离恰好为m的点对数目。
分析：树的分治。
	我们每次寻找一棵子树，选择该子树的重心作为根，计算出子树上的每个节点到根的距离。
	考虑点对 (x,y)的距离为m，那么有 dis[x]+dis[y] = m，这是在 x 和 y 的lca为根的情况下的关系。
	那么，如果不满足条件呢？利用类似于容斥原理的思想，减掉子树中的点对即可。

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
#include <utility>
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

const int MAXN = 2e4+5;

struct node{
    int y,val,next;
}edge[MAXN<<1];

int po[MAXN],tol;
int dmax[MAXN],sz[MAXN];
int dis[MAXN];
bool use[MAXN];
ll ans;
int n,m;

void dfsSz(int x,int fa){
    sz[x] = 1;
    dmax[x] = 0;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(use[y]||y==fa)continue;
        dfsSz(y,x);
        sz[x] += sz[y];
        cmax( dmax[x],sz[y] );
    }
}

int tot,root;
void dfsRoot(int x,int fa){
    cmax( dmax[x],tot-sz[x] );
    if(dmax[root]>dmax[x])
        root = x;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(use[y]||y==fa)continue;
        dfsRoot(y,x);
    }
}

int tp;
void dfsCal(int x,int fa,int dep){
    dis[++tp] = dep;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(use[y]||y==fa)continue;
        dfsCal(y,x,dep+edge[i].val);
    }
}

ll cal(int x,int dep){
    ll tmp = 0;
    tp = 0;

    dfsCal(x,0,dep);
    sort(dis+1,dis+tp+1);

    int l = 1 , r = tp;
    while(l<=r){
        if(dis[l]+dis[r]<m)
            l ++;
        else if(dis[l]+dis[r]>m)
            r --;
        else{
            if(dis[l]==dis[r]){
                tmp += ll(r-l+1)*(r-l)/2;
                break;
            }else{
                int pl = l;
                int pr = r;
                while(dis[l]==dis[pl])
                    l ++;
                while(dis[r]==dis[pr])
                    r --;
                tmp += ll(pr-r)*(l-pl);
            }
        }
    }
    return tmp;
}

void dfsAns(int x){
    dfsSz(x,0);
    tot = sz[x];
    root = x;
    dfsRoot(x,0);

    ans += cal(root,0);
    use[root] = true;

    for(int i=po[root];i;i=edge[i].next){
        int y = edge[i].y;
        if(use[y])continue;
        ans -= cal(y,edge[i].val);
        dfsAns(y);
    }
}

void add(int x,int y,int val){
    edge[++tol].y = y;
    edge[tol].val = val;
    edge[tol].next = po[x];
    po[x] = tol;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int y,val;
    while(cin>>n,n){
        Clear(po);
        tol = 0;

        rep1(x,n){
            while(RD(y),y){
                RD(val);
                add(x,y,val);
                add(y,x,val);
            }
        }

        while(RD(m),m){
            Clear(use);
            ans = 0;
            dfsAns(1);
            puts(ans?"AYE":"NAY");
        }
        puts(".");
    }

	return 0;
}
