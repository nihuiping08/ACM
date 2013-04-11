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

/******** program ********************/

const int MAXN = 1005;
const int MAXM = 100005;
const int INF = 1e9;

int po[MAXN],tol;
int gap[MAXN],dis[MAXN],arc[MAXN],pre[MAXN],cur[MAXN];
int n,m,s,t,d;

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

