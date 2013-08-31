/*

分析：
　　由于每个人只有一个最讨厌的人，构造出的图形一个连通块里最多只有一个基环，
	假设为root...-ban-root。
　　显然最优值从选取root或者不选取root中选出。
　　考虑到如果是奇数环时，选取了root，就不能再选取ban。如果不选root的话，ban可选可不选。
　　于是我们考虑两种情况：
　　1.强制root不选，ban随意。
　　2.强制ban不选，root随意。
　　先dfs找到root以及ban，对于两种情况分别进行树上DP即可。

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

const int MAXN = 1e6+5;

int po[MAXN],tol;
ll dp[MAXN][2];
int val[MAXN],n;

struct Edge{
    int y,next;
}edge[MAXN<<1];

inline void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

int root,ban;
bool use[MAXN],vis[MAXN][2];

void dfsCir(int x,int fa){
    use[x] = true;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)continue;
        if(!use[y])dfsCir(y,x);
        else    root = x , ban = y;
    }
}

void dfsAns(int x){
    dp[x][0] = 0;
    dp[x][1] = val[x];
    vis[x][0] = 1;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(vis[y][0])continue;
        dfsAns(y);
        dp[x][0] += max(dp[y][0],dp[y][1]);
        dp[x][1] += dp[y][0];
    }
}

void dfsBan(int x){
    dp[x][0] = 0;
    dp[x][1] = val[x];
    vis[x][1] = 1;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(vis[y][1])continue;
        dfsBan(y);
        if(y==ban){
            dp[x][0] += dp[y][0];
            dp[x][1] += dp[y][0];
        }else{
            dp[x][0] += max(dp[y][0],dp[y][1]);
            dp[x][1] += dp[y][0];
        }
    }
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    while(~RD(n)){
        Clear(po);
        tol = 0;
        int y;
        rep1(x,n){
            RD2(val[x],y);
            add(x,y);
            add(y,x);
        }

        Clear(dp);
        Clear(use);
        Clear(vis);

        ll ans = 0;
        rep1(i,n)
            if(!use[i]){
                ban = 0;
                root = i;
                dfsCir(i,0);

                dfsAns(root);
                ll tmp = dp[root][0];

                dfsBan(root);
                ans += max( tmp,max(dp[root][0],dp[root][1]) );
            }
        cout<<ans<<endl;
    }

    return 0;
}
