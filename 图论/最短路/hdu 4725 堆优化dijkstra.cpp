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

const int MAXN = 1e5+5;
const int INF = 1e9+7;

struct Edge{
    int y,cost,next;
}edge[MAXN<<1];

int po[MAXN],tol;
vector<int> vec[MAXN];
int la[MAXN],n,per,m;
int dis[MAXN];
bool use[MAXN];
bool ok[MAXN];

struct node{
    int x,cost;
    friend bool operator < (node a,node b){
        return a.cost>b.cost;
    }
    node(){}
    node(int _x,int _cost):x(_x),cost(_cost){}
};

int dijkstra(){
    priority_queue<node> q;
    Clear(use);
    rep1(i,n)dis[i] = INF;
    q.push(node(1,0));
    dis[1] = 0;
    Clear(ok);
    while(!q.empty()){
        node p = q.top();
        q.pop();
        int x = p.x;
        if(use[x])continue;
        use[x] = 1;
        if(x==n&&dis[n]<INF)break;

        if(!ok[la[x]]){
                ok[la[x]] = 1;
                int now = la[x]-1;
                if(now)
                    foreach(i,vec[now]){
                        int y = vec[now][i];
                        if(!use[y]&&dis[x]+per<dis[y]){
                            dis[y] = dis[x]+per;
                            q.push(node(y,dis[y]));
                        }
                    }
                now += 2;
                if(now<=n)
                    foreach(i,vec[now]){
                        int y = vec[now][i];
                        if(!use[y]&&dis[x]+per<dis[y]){
                            dis[y] = dis[x]+per;
                            q.push(node(y,dis[y]));
                        }
                    }
        }
        for(int i=po[x];i;i=edge[i].next){
            int y = edge[i].y;
            int tmp = edge[i].cost+dis[x];
            if(!use[y]&&tmp<dis[y]){
                dis[y] = tmp;
                q.push(node(y,dis[y]));
            }
        }
    }

    return dis[n];
}

inline void add(int x,int y,int cost){
    edge[++tol].y = y;
    edge[tol].cost = cost;
    edge[tol].next = po[x];
    po[x] = tol;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("cf.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int x,y,c,ncase,Ncase = 0;
    RD(ncase);
    while(ncase--){
        printf("Case #%d: ",++Ncase);
        RD3(n,m,per);
        rep1(i,n)
            vec[i].clear();
        rep1(i,n){
            RD(la[i]);
            vec[la[i]].pb(i);
        }

        Clear(po);
        tol = 0;
        while(m--){
            RD3(x,y,c);
            add(x,y,c);
            add(y,x,c);
        }

        int ans = dijkstra();
        printf("%d\n",ans==INF?-1:ans);
    }

    return 0;
}