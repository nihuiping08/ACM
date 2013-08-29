/*
题目：给出一棵树，对于每个节点有一个等级（A-Z，A最高），如果两个不同的节点有相同等级
	的父节点（节点不一定相同），则两个节点的路径上最少有一个比他们两的等级都高的节点。
	要求输出1~n的等级。

分析：
	考虑一条链的情况，如果把A放中间，把数列分成两段，对于每一段，中间放B，这样分成了四段，
	对于每一段继续这样分，显然26个字母可以安放2^26个位置。

　　对于树这种结构的话，如何安放？

　　类似于一条链的情况，根放A，然后分成的每一条子链中间放B。。。

　　但是怎么知道中间的B在哪呢？

　　不妨考虑树的点分治
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

int ch[MAXN];
int po[MAXN],tol;
int sz[MAXN],dmax[MAXN];
bool use[MAXN];

struct node{
    int y,next;
}edge[MAXN<<1];

inline void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

void dfsSize(int x,int fa){
    dmax[x] = 0;
    sz[x] = 1;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(use[y]||y==fa)continue;
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
        if(use[y]||y==fa)continue;
        dfsRoot(y,x);
    }
}

void dfsAns(int x,int dep){
    dfsSize(x,0);

    root = x;
    tot = sz[x];
    dfsRoot(x,0);

    ch[root] = dep;
    use[root] = true;

    for(int i=po[root];i;i=edge[i].next){
        int y = edge[i].y;
        if(!use[y])dfsAns(y,dep+1);
    }
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int n,x,y;
    while(cin>>n){
        Clear(po);
        tol = 0;
        REP(i,2,n){
            RD2(x,y);
            add(x,y);
            add(y,x);
        }
        Clear(use);
        dfsAns(1,0);

        rep1(i,n)
            printf("%c ", char(ch[i]+'A') );
        puts("");
    }

    return 0;
}
