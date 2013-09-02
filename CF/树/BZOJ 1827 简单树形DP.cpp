/*

分析：

　　先以1（随便）为根dfs一次，求出以每个节点为根时，他所在的子树的人数个数sz，并且计算
	出以1为根时的不方便度。

　　第二次时，继续以1为根，这时假设当前节点为x，不方便度为cost，儿子节点为y。把x的不
	方便度cost向y转化，其实就是cost+(sz[1]-2*sz[y])*edge[i].cost （画个图就知道了。。。）

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
const ll INF = 1e15;

struct Edge{
    int y,cost,next;
}edge[MAXN<<1];

int c[MAXN],n;
ll dp[MAXN],sz[MAXN],ans[MAXN];
int po[MAXN],tol;

inline void add(int x,int y,int cost){
    edge[++tol].y = y;
    edge[tol].cost = cost;
    edge[tol].next = po[x];
    po[x] = tol;
}

void dfsDp(int x,int fa){
    dp[x] = 0;
    sz[x] = c[x];
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)continue;
        dfsDp(y,x);
        sz[x] += sz[y];
        dp[x] += sz[y]*edge[i].cost+dp[y];
    }
}

void dfsAns(int x,int fa,ll cost){
    ans[x] = cost;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)continue;
        ll tmp = cost+(sz[1]-2*sz[y])*edge[i].cost;
        dfsAns(y,x,tmp);
    }
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    while(~RD(n)){
        rep1(i,n)
            RD(c[i]);
        int x,y,cost;
        REP(i,2,n){
            RD3(x,y,cost);
            add(x,y,cost);
            add(y,x,cost);
        }

        dfsDp(1,0);
        dfsAns(1,0,dp[1]);

        ll tmp = INF;
        rep1(i,n)
            cmin(tmp,ans[i]);
        cout<<tmp<<endl;
    }

    return 0;
}
