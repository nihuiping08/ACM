/*

题目：删除一条边之后，从1到n的最坏最短路
分析：枚举最短路上的边，对于删除后求一次最短路即可

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

const int MAXN = 1005;
const int MAXM = 1e5+5;
const int INF  = 1e9;

struct node{
    int y,val,id,next;
}edge[MAXM];

int po[MAXN],tol;
int dis[MAXN],n;
PII pre[MAXN],path[MAXN];
bool use[MAXN];
bool is[MAXN];

void add(int x,int y,int val,int id){
    edge[++tol].y = y;
    edge[tol].val = val;
    edge[tol].next = po[x];
    edge[tol].id = id;
    po[x] = tol;
}

int spfa(int bad){
    queue<int> q;
    rep1(i,n)
        dis[i] = INF;
    dis[1] = 0;
    Clear(use);

    q.push(1);
    pre[1] = MP(0,0);

    while(q.size()){
        int x = q.front();
        q.pop();
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            if( edge[i].id==bad )continue;
            int y = edge[i].y;
            int val = edge[i].val+dis[x];
            if(dis[y]>val){
                dis[y] = val;
                pre[y] = MP(x,edge[i].id);
                if(!use[y]){
                    use[y] = true;
                    q.push(y);
                }
            }
        }
    }
    return dis[n];
}

void dfs(int now,int &ans){
    if(now==1)return;
    int tmp = spfa(path[now].second);
    cmax( ans,tmp );
    dfs(path[now].first,ans);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int x,y,m,val,ncase;
    RD(ncase);
    while(ncase--){
        Clear(po);
        tol = 0;
        RD2(n,m);
        while(m--){
            RD3(x,y,val);
            add(x,y,val,m);
            add(y,x,val,m);
        }

        spfa(MAXM);
        rep1(i,n)
            path[i] = pre[i];
        int ans = 0;
        dfs(n,ans);
        if(ans==INF)
            puts("-1");
        else
            cout<<ans<<endl;
    }

	return 0;
}
