/*

题目：还是自己看题目吧

trick：当不连通时不需要人去炸。否则，当桥的费用为0时当然需要一个人去炸。。。

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

char IN;
bool NEG;
inline void Int(int &x){
    NEG = 0;
    while(!isdigit(IN=getchar()))
        if(IN=='-')NEG = 1;
    x = IN-'0';
    while(isdigit(IN=getchar()))
        x = x*10+IN-'0';
    if(NEG)x = -x;
}
inline void LL(ll &x){
    NEG = 0;
    while(!isdigit(IN=getchar()))
        if(IN=='-')NEG = 1;
    x = IN-'0';
    while(isdigit(IN=getchar()))
        x = x*10+IN-'0';
    if(NEG)x = -x;
}

/******** program ********************/

const int MAXN = 1005;
const int INF = 1e9;

int low[MAXN],dfn[MAXN],dep;
int po[MAXN],tol;
int best;

struct Edge{
    int y,cost,id,next;
}edge[MAXN*MAXN<<1];

void add(int x,int y,int cost,int id){
    edge[++tol].y = y;
    edge[tol].cost = cost;
    edge[tol].id = id;
    edge[tol].next = po[x];
    po[x] = tol;
}

void dfs(int x,int fid){
    dfn[x] = low[x] = ++ dep;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        int id = edge[i].id;
        if(id==fid)continue;
        if(!dfn[y]){
            dfs(y,id);
            cmin(low[x],low[y]);
            if(low[y]>dfn[x]){
                if(edge[i].cost<best)
                    best = edge[i].cost;
            }
        }else cmin(low[x],dfn[y]);
    }
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int size = 256 << 20; // 256MB
    char *p = (char*)malloc(size) + size;
    __asm__("movl %0, %%esp\n" :: "r"(p) );

    int n,m,x,y,cost;
    while(RD2(n,m),n||m){
        Clear(po);
        tol = 0;
        rep1(i,m){
            RD3(x,y,cost);
            if(x>n||y>n)continue;
            add(x,y,cost,i);
            add(y,x,cost,i);
        }

        dep = 0;
        Clear(dfn);
        best = INF;
        int ok = 0;

        rep1(i,n)
            if(!dfn[i]){
                ok ++;
                dfs(i,0);
            }
        if(best==0)best = 1;
        if(ok>1)best = 0;
        printf("%d\n",best==INF?-1:best);
    }

    return 0;
}
