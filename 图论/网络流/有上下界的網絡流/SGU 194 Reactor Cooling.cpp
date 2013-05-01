/*

題目：
    有向圖中，對於每條邊有容量限制 l_ij <= f_ij <= cap_ij
    求是否有可行流。

分析：
    無源匯可行流。
    1.對於每條邊，x y l cap，建立邊 x y (cap-l)。

    2.對於每個頂點，x，若sigma(入度)>sigma(出度)，建立邊x t 差
    否則建立 s t 差

*/
#include <set>
#include <map>
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

#define lx(x) (x<<1)
#define rx(x) (x<<1|1)
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

/******** program ********************/

const int MAXN = 405;
const int MAXM = 100005;
const int INF = 1e9;

int pre[MAXN],cur[MAXN],gap[MAXN],dis[MAXN],arc[MAXN];
int po[MAXN],tol;
int limit[MAXM],du[MAXN];
int n,m,s,t;

struct node{
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
    gap[0] = t;
    rep1(i,t)
        arc[i] = po[i];

    int ans = 0;
    int aug = INF;
    int x = s;

    while(dis[s]<t){
        bool ok = false;
        cur[x] = aug;
        for(int i=arc[x];i;i=edge[i].next){
            int y = edge[i].y;
            if(edge[i].f>0&&dis[y]+1==dis[x]){
                ok = true;
                pre[y] = arc[x] = i;
                aug = min(aug,edge[i].f);
                x = y;
                if(x==t){
                    ans += aug;
                    while(x!=s){
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
        int MIN = t-1;
        for(int i=po[x];i;i=edge[i].next)
            if(edge[i].f>0&&dis[edge[i].y]<MIN){
                MIN = dis[edge[i].y];
                arc[x] = i;
            }
        if(--gap[dis[x]]==0)
            break;
        dis[x] = ++ MIN;
        ++ gap[dis[x]];
        if(x!=s){
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

    int x,y,cap;
    while(~RD2(n,m)){
        tol = 1;
        s = n+1;
        t = n+2;
        memset(po,0,sizeof(po));
        memset(du,0,sizeof(du));

        rep1(i,m){
            RD4(x,y,limit[i],cap);
            add( x,y,cap-limit[i] );
            du[y] += limit[i];
            du[x] -= limit[i];
        }

        rep1(i,n){
            if(du[i]>0)
                add( s,i,du[i] );
            else if(du[i]<0)
                add( i,t,-du[i] );
        }

        sap();

        bool ok = true;
        for(int i=po[s];i;i=edge[i].next)
            if(edge[i].f>0){
                ok = false;
                break;
            }

        if(ok){
            puts("YES");
            for(int i=1;i<=m;i++)
                printf("%d\n",limit[i]+edge[i<<1|1].f);
        }else
            puts("NO");

    }

	return 0;
}
