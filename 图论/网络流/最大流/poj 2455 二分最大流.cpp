/*

题目：p条路，连接n个节点，现在需要从节点1到节点n，不重复走过一条路且走t次，
	最小化这t次中连接两个节点最长的那条路的值。

分析：二分答案，对于<=二分的值的边建边，跑一次最大流即可。

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
const int MAXM = 100005;
const int INF = 1e9;

int po[MAXN],tol;
int gap[MAXN],dis[MAXN],arc[MAXN],pre[MAXN],cur[MAXN];
int n,m,vs,vt,t;

struct Edge{
    int y,f,next;
}edge[MAXM];

struct node{
    int x,y,l;
}p[MAXM];

void Add(int x,int y,int f){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].next = po[x];
    po[x] = tol;
}
void add(int x,int y,int f){
    Add(x,y,f);
    Add(y,x,f); // here
}

int sap(){
    memset(dis,0,sizeof(dis));
    memset(gap,0,sizeof(gap));
    gap[0] = vt;
    rep1(i,vt)
        arc[i] = po[i];

    int ans = 0;
    int aug = INF;
    int x = vs;

    while(dis[vs]<vt){
        bool ok = false;
        cur[x] = aug;
        for(int i=arc[x];i;i=edge[i].next){
            int y = edge[i].y;
            if(edge[i].f>0&&dis[y]+1==dis[x]){
                ok = true;
                pre[y] = arc[x] = i;
                aug = min(aug,edge[i].f);
                x = y;
                if(x==vt){
                    ans += aug;
                    while(x!=vs){
                        edge[pre[x]].f -= aug;
                        edge[pre[x]^1].f += aug;
                        x = edge[pre[x]^1].y;
                    }
                    aug = INF;
                }
                break;
            }
        }
        if(ok)
            continue;
        int MIN = vt-1;
        for(int i=po[x];i;i=edge[i].next)
            if(edge[i].f>0&&dis[edge[i].y]<MIN){
                MIN = dis[edge[i].y];
                arc[x] = i;
            }
        if(--gap[dis[x]]==0)
            break;
        dis[x] = ++ MIN;
        ++ gap[dis[x]];
        if(x!=vs){
            x = edge[pre[x]^1].y;
            aug = cur[x];
        }
    }
    return ans;
}

inline bool ok(int mid){
    Clear(po);
    tol = 1;

    vs = 1;
    vt = n;

    rep1(i,m)
        if(p[i].l<=mid)
            add(p[i].x,p[i].y,1);

    return sap()>=t;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    while(~RD3(n,m,t)){
        int l = 10000000 , r = 0;
        rep1(i,m){
            RD3(p[i].x,p[i].y,p[i].l);
            cmin(l,p[i].l);
            cmax(r,p[i].l);
        }

        int ans = 0;
        while(l<=r){
            int mid = (l+r)>>1;
            if(ok(mid)){
                r = mid-1;
                ans = mid;
            }else
                l = mid+1;
        }
        cout<<ans<<endl;
    }

    return 0;
}
