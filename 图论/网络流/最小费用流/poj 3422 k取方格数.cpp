/*

题目：给出n*n的方格矩阵，现在从左上方走m次到右下方，问m次能够获得的最大价值和。

分析：最大费用流。拆点进行限制每个格子只取一次，假设点x拆成 x,xx，右边（假设有）y,yy，
下方（假设有）z,zz

　　     点  点    流量 费用

　　则：x , xx , 1 , -a[i][j]

  　　  x , xx , m  , 0

　　　 xx,  y  , m  , 0

　　　 xx , z  , m  , 0 　

用最小费用流增广m次即可

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
    while( !isdigit(op=getchar()) );
    x = op-'0';
    while(isdigit(op=getchar()))
        x = x*10+op-'0';
}

const int MAXN = 5005;
const int MAXM = 200005;
const int INF = 1e9;

int pre[MAXN],dis[MAXN];
int po[MAXN],tol;
bool use[MAXN];
int q[MAXM],head,tail;
int n,m,vs,vt,ans;
int a[55][55];

struct node{
    int y,f,cost,next;
}edge[MAXM];

inline void Add(int x,int y,int f,int cost){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].cost = cost;
    edge[tol].next = po[x];
    po[x] = tol;
}

inline void add(int x,int y,int f,int cost){
    Add(x,y,f,cost);
    Add(y,x,0,-cost);
}

inline bool spfa(){
    memset(use,false,sizeof(use));
    rep1(i,vt)
        dis[i] = INF;
    dis[vs] = 0;
    head = tail = 0;
    q[tail++] = vs;
    pre[vs] = 0;
    while(head<tail){
        int x = q[head++];
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            int y = edge[i].y;
            if(edge[i].f>0&&edge[i].cost+dis[x]<dis[y]){
                dis[y] = dis[x]+edge[i].cost;
                pre[y] = i;
                if(!use[y]){
                    use[y] = true;
                    q[tail++] = y;
                }
            }
        }
    }
    if(dis[vt]==INF)
        return false;
    int aug = INF;
    for(int i=pre[vt];i;i=pre[edge[i^1].y])
        aug = min(aug,edge[i].f);
    for(int i=pre[vt];i;i=pre[edge[i^1].y]){
        edge[i].f -= aug;
        edge[i^1].f += aug;
    }
    ans += dis[vt]*aug;
    return true;
}

inline int id(int x,int y){
    return (x-1)*n+y;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    while(~RD2(n,m)){
        int nn = n*n;
        vs = 1;
        vt = nn<<1;

        tol = 1;
        Clear(po);

        rep1(i,n)
            rep1(j,n)
                Int(a[i][j]);
                //RD(a[i][j]);

        rep1(i,n){
            rep1(j,n){
                int now = id(i,j);
                add( now,now+nn,1,-a[i][j] );
                add( now,now+nn,m,0 );
                if(i<n) add( now+nn,now+n,m,0 );
                if(j<n) add( now+nn,now+1,m,0 );
            }
        }

        ans = 0;
        while(m--&&spfa())
            ;
        cout<<-ans<<endl;
    }

    return 0;
}
