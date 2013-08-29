/*

题目：找出树上的点对(x,y)数目，满足两者距离<=d

分析：
	
	经典题：树的分治
	
	找到一个作为树根，定义dis[x]表示节点x到根的距离。
	那么，如果(x,y)不在同一个树根的同一个子树时，有dis[x]+dis[y]<=d的话，就算一个点对。
	
	考虑在呢？
	
	可以利用类似于容斥原理的思想，先把在和不在都算了，然后减掉儿子树的在和不在的，加上
	子树的子树在和不在的。。。最后就是答案。。。
	
	但是这样随便找的话，会TLE。。。
	
	考虑如果每次找的时候都是树的重心，那么，均摊下来的时间复杂度为 n logn * logn
	所以直接对于每棵子树，先找到树的重心，在计算即可。
	
	对于某个节点的计算：利用双指针扫即可。

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

const int MAXN = 20005;

int po[MAXN],tol;
int dis[MAXN];
bool use[MAXN];
int sz[MAXN];
int dmax[MAXN];
ll ans;
int n,m;

struct node{
    int y,val,next;
}edge[MAXN];

void dfsSize(int x,int fa){
    dmax[x] = 0;
    sz[x] = 1;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa||use[y])continue;
        dfsSize(y,x);
        sz[x] += sz[y];
        cmax( dmax[x] , sz[y] );
    }
}

int root,tot;
void dfsRoot(int x,int fa){
    cmax( dmax[x] , tot-sz[x] );
    if(dmax[x]<dmax[root])
        root = x;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa||use[y])continue;
        dfsRoot(y,x);
    }
}

int top;
void dfsCal(int x,int fa,int dep){
    dis[++top] = dep;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa||use[y])continue;
        dfsCal(y,x,dep+edge[i].val);
    }
}

ll cal(int x,int val){
    top = 0;
    dfsCal(x,0,val);

    sort(dis+1,dis+top+1);
    ll tmp = 0;

    int r = top;
    for(int l=1;l<=r;l++){
        while(dis[r]+dis[l]>m&&l<r)
            r --;
        tmp += r-l;
    }

    return tmp;
}

void dfsAns(int x){
    dfsSize(x,0);
    root = x;
    tot = sz[x];
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

    int x,y,val;
    while(cin>>n>>m,n||m){
        Clear(po);
        tol = 0;

        REP(i,2,n){
            RD3(x,y,val);
            add(x,y,val);
            add(y,x,val);
        }

        ans = 0;
        Clear(use);
        dfsAns(1);
        cout<<ans<<endl;
    }

    return 0;
}
