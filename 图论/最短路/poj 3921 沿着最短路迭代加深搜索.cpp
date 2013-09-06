/*

题目：给出一个图，问最少删除多少个点，使得从点1到点n经过的点数超过k个。

分析：

　　上网搜了一下，发现很多人用网络流做的，发现我不会。再后来看到这篇说网络流的做法是错的，囧。

　　后来发现点数有点少，直接上爆搜。每次搜索前先跑一遍最短路，判断是否满足，如果满足更
	新答案，退出。

　　否则，在求最短路时记录一下路径，然后枚举删除最短路上的点，继续搜。

　　第一次写时，记录路径用的是全局变量，每次搜下一层的时候就会变，发现居然也A了。。。

　　我试了一下，发现n不会等于1。。。

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

char op;
inline void Int(int &x){
    while(!isdigit(op=getchar()));
    x = op-'0';
    while(isdigit(op=getchar()))
        x = x*10+op-'0';
}

const int MAXN = 55;
const int MAXM = 4010;
const int INF = 1e9;

int g[MAXN][MAXN];
int dis[MAXN],n,m,k;
bool bad[MAXN],use[MAXN];
int pre[MAXN];

bool dijkstra(){
    rep1(i,n)
        dis[i] = INF;
    Clear(use);
    dis[1] = 0;
    int now , MIN;
    pre[1] = 0;
    rep(q,n){
        MIN = INF;
        rep1(j,n)
            if(!bad[j]&&!use[j]&&dis[j]<MIN)
                MIN = dis[now=j];
        if(MIN==INF)
            break;
        use[now] = true;
        rep1(j,n)
            if(!bad[j]&&!use[j]){
                if(dis[j]>dis[now]+g[now][j]){
                    pre[j] = now;
                    dis[j] = dis[now]+g[now][j];
                }
            }
    }
    return dis[n]>k;
}

int ans;
void dfs(int res,int sum){
    if(sum>=ans)return;
    if( dijkstra() ){
        ans = sum;
        return;
    }
    if(!res)
        return;

    int path[MAXN]; // 得要在每次搜索时记录
    copy(pre,pre+n+1,path);

    int x = n;
    while(path[x]){
        x = path[x];
        if(x==1)continue;
        bad[x] = true;
        dfs(res-1,sum+1);
        bad[x] = false;
    }
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int x,y;
    while(true){
        Int(n);Int(m);Int(k);
        if(!n&&!m&&!k)break;
        rep1(i,n)
            rep1(j,n)
                g[i][j] = INF;
        while(m--){
            Int(x);Int(y);
            g[x][y] = 1;
        }

        Clear(bad);
        ans = INF;
        dfs(n-1,0);
        printf("%d\n",ans);
    }

    return 0;
}
