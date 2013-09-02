/*

分析：
　　初看时没什么想法，想到询问的是最短时间，显然满足单调性，于是yy了一下就出来了。
　　二分答案，通过最大流判断答案是否可行。
　　当然，这题重点在于如何建图。
　　我们先预处理出所有的巫妖与小精灵的关系，判断“巫妖看到小精灵的视线没有被树木阻挡”时，
	可以用海伦公式求三角形的面积来判断，题目要求不能有任何一个点，所以对于两点只与圆相切
	于一点也算。

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


const int MAXN = 505;
const int MAXM = 100005;
const int INF = 1e9;
const double eps = 1e-8;

bool use[205][205];
int po[MAXN],tol;
int gap[MAXN],dis[MAXN],arc[MAXN],pre[MAXN],cur[MAXN];
int n,m,kk,vs,vt;

struct A{
    int x,y,r,t;
    inline void rd(){
        RD4(x,y,r,t);
    }
}a[MAXN];

struct B{
    int x,y;
    inline void rd(){
        RD2(x,y);
    }
}b[MAXN];

struct C{
    int x,y,r;
    inline void rd(){
        RD3(x,y,r);
    }
}c[MAXN];

struct node{
    int y,f,next;
}edge[MAXM];

inline void Add(int x,int y,int f){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].next = po[x];
    po[x] = tol;
}
inline void add(int x,int y,int f){
    Add(x,y,f);
    Add(y,x,0);
}

inline int sap(){
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

inline int cdis(int x,int y){
    return x*x+y*y;
}

inline bool check(A pa,B pb,C pc){
    double a = sqrt( cdis(pa.x-pb.x,pa.y-pb.y)*1.0 );
    double b = sqrt( cdis(pc.x-pb.x,pc.y-pb.y)*1.0 );
    double c = sqrt( cdis(pa.x-pc.x,pa.y-pc.y)*1.0 );
    double p = (a+b+c)/2;
    double s = p*(p-a)*(p-b)*(p-c); // 海伦公式
    double tmp = a*pc.r/2;
    tmp *= tmp;
    if( tmp>=s )
        return false;
    return true;
}

inline void init(){ // 预处理
    rep1(i,n){ // x,y,r,t
        rep1(j,m){ // x,y
            if( cdis(a[i].x-b[j].x,a[i].y-b[j].y)>a[i].r*a[i].r ){
                use[i][j] = false;
                continue;
            }
            use[i][j] = true;
            rep1(k,kk){ // x,y,r
                if(!check(a[i],b[j],c[k])){
                    use[i][j] = false;
                    break;
                }
            }
        }
    }
}

inline bool ok(int mid){ // 判断二分的答案是否可行
    vs = MAXN-3;
    vt = vs+1;

    Clear(po);
    tol = 1;

    rep1(i,n)
        add(vs,i,mid/a[i].t+1);
    rep1(i,n)
        rep1(j,m)
            if(use[i][j])
                add(i,j+n,1);
    rep1(j,m)
        add(j+n,vt,1);
    return sap()>=m;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    while(~RD3(n,m,kk)){
        rep1(i,n)
            a[i].rd();
        rep1(i,m)
            b[i].rd();
        rep1(i,kk)
            c[i].rd();

        init(); // 预处理

        int l = 0 , r = INF;
        int ans = -1;

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
