/*

题目：
一棵树上有n个节点，编号分别为1到n，每个节点都有一个权值w。我们将以下面的形式来要求你对
这棵树完成一些操作： 
I. CHANGE u t : 把结点u的权值改为t 
II. QMAX u v: 询问从点u到点v的路径上的节点的最大权值 
III. QSUM u v: 询问从点u到点v的路径上的节点的权值和 
注意：从点u到点v的路径上的节点包括u和v本身

分析：裸的树链剖分

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
const int INF = 1e9;

int val[MAXN];
int po[MAXN],tol;
int sz[MAXN],dep[MAXN],fa[MAXN],son[MAXN],tid[MAXN],top[MAXN];
bool use[MAXN];
int tot;
int mx,msum;

struct node{
    int y,next;
}edge[MAXN];

struct Tree{
    int l,r,mx,sum;
    inline int mid(){
        return (l+r)>>1;
    }
}tree[MAXN<<2];

inline void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

void dfsFind(int x,int pa,int depth){
    use[x] = true;
    dep[x] = depth;
    fa[x] = pa;
    sz[x] = 1;
    son[x] = 0;

    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(use[y])continue;
        dfsFind(y,x,depth+1);
        sz[x] += sz[y];
        if(sz[y]>sz[ son[x] ])
            son[x] = y;
    }
}

void dfsCon(int x,int pa){
    use[x] = true;
    tid[x] = ++ tot;
    top[x] = pa;
    if(son[x])
        dfsCon(son[x],pa);
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(use[y])continue;
        dfsCon(y,y);
    }
}

inline void update(int rt){
    tree[rt].sum = tree[rt<<1].sum+tree[rt<<1|1].sum;
    tree[rt].mx = max( tree[rt<<1].mx , tree[rt<<1|1].mx );
}

void build(int l,int r,int rt){
    tree[rt].l = l;
    tree[rt].r = r;
    if(l==r){
        tree[rt].sum = tree[rt].mx = val[l];
        return;
    }
    int mid = tree[rt].mid();
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);

    update(rt);
}

void modify(int pos,int c,int rt){
    if(tree[rt].l==tree[rt].r){
        tree[rt].sum = tree[rt].mx = c;
        return;
    }
    int mid = tree[rt].mid();
    if(pos<=mid)
        modify(pos,c,rt<<1);
    else
        modify(pos,c,rt<<1|1);

    update(rt);
}

void ask(int l,int r,int rt){
    if(tree[rt].l==l&&tree[rt].r==r){
        mx = max(mx,tree[rt].mx);
        //cmax( mx , tree[rt].mx );
        msum += tree[rt].sum;
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

    int n,m,x,y;
    while(cin>>n){
        Clear(po);
        tol = 1;

        REP(i,2,n){
            RD2(x,y);
            add(x,y);
            add(y,x);
        }

        Clear(use);
        dfsFind(1,1,1);

        Clear(use);
        tot = 0;
        dfsCon(1,1);

        rep1(i,n){
            RD(y);
            val[ tid[i] ] = y;
        }

        build(1,n,1);

        RD(m);
        char op[10];
        while(m--){
            scanf("%s%d%d",op,&x,&y);
            if(op[1]=='H'){
                modify(tid[x],y,1);
            }else{
                mx = -INF;
                msum = 0;

                while( top[x] != top[y] ){
                    if( dep[ top[x] ] < dep[ top[y] ] )
                        swap(x,y);
                    ask( tid[ top[x] ] , tid[x] , 1 );
                    x = fa[ top[x] ];
                }
                if(dep[x]>dep[y])
                    swap(x,y);
                ask(tid[x],tid[y],1);

                printf("%d\n",op[1]=='M'?mx:msum);
            }
        }
    }

    return 0;
}
