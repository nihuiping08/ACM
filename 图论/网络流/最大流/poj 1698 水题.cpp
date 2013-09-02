/*

题目：给出n部电影的可以在周几拍摄、总天数、期限，问能不能把n部电影接下来。

分析：

　　对于每部电影连上源点，流量为总天数。

　　对于每一天建立一个点，连上汇点，流量为为1。

　　对于每部电影，如果可以在该天拍摄，则连上一条流量为1的边。

　　跑一次最大流。。。

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
int n,m,vs,vt;

struct Edge{
    int y,f,next;
}edge[MAXM];

void Add(int x,int y,int f){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].next = po[x];
    po[x] = tol;
}
void add(int x,int y,int f){
    Add(x,y,f);
    Add(y,x,0);
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

int f[10],w,d;

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    while(ncase--){
        Clear(po);
        tol = 1;
        vs = MAXN-3;
        vt = vs+1;

        int ans = 0;
        int t = 0;
        RD(n);
        rep1(i,n){
            rep(j,7)
                RD(f[j]);
            RD2(d,w);
            ans += d;

            add(vs,i,d);
            w *= 7;
            rep(j,w)
                if(f[j%7])
                    add(i,j+n+1,1);

            cmax(t,w);
        }
        rep1(i,t)
            add(i+n,vt,1);
        ans -= sap();
        puts(ans==0?"Yes":"No");
    }

    return 0;
}
