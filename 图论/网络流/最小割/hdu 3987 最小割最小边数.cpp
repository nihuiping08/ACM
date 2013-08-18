/*

题目：求最小割的最小边数
分析：
	方法一：构图时，边权置为 (max_edge+1)*cost+1，求一边最大流，则答案为 max_flow % (max_edge+1)
	方法二：求一边最大流，对于最大流重新建图，边权为1即可

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
const int MAXM = 400005;
const int INF = 1e9;

int po[MAXN],tol;
ll gap[MAXN],dis[MAXN],arc[MAXN],pre[MAXN],cur[MAXN];
int n,m,vs,vt;

struct node{
    int y,next;
    ll f;
}edge[MAXM];

void Add(int x,int y,ll f){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].next = po[x];
    po[x] = tol;
}
void add(int x,int y,ll f){
    Add(x,y,f);
    Add(y,x,0);
}

ll sap(){
    memset(dis,0,sizeof(dis));
    memset(gap,0,sizeof(gap));
    gap[0] = vt;
    rep1(i,vt)
        arc[i] = po[i];

    ll ans = 0;
    ll aug = INF;
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

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    rep1(Ncase,ncase){
        tol = 1;
        RD2(n,m);
        vt = n;
        vs = 1;
        memset(po,0,sizeof(po[0])*(vt+10));

        int x,y,z,od;
        ll big = m+1;
        while(m--){
            RD4(x,y,z,od);
            x ++;
            y ++;
            //cout<<x<<" "<<y<<" "<<z<<" "<<od<<endl;
            add(x,y,z*big+1);
            if(od)
                add(y,x,z*big+1);
        }
        printf("Case %d: %I64d\n",Ncase,sap()%big);
    }

	return 0;
}
