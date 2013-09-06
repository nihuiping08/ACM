/*

一场比赛必然有一个赢家和一个输家，但是似乎不太好同时在模型中表示。不妨先假设后面的M场比
赛中双方都是输家，这样我们只要在模型中表示一方成为赢家即可。

至此应该有一个初步的模型了：对于N支球队和M场比赛各建一个点，从源向每场比赛连流量1费用0的
边，从比赛向参与这场比赛的两支队伍各连一条流量1费用0的边。剩下的就是队伍收益的费用表示了。

我们考虑费用的增量：多赢一场比赛产生的收益。即
(C*(w+1)^2+D*(l-1)^2)-(C*w^2+D*l^2)=2w*C-2l*D+C+D。对于第i支队伍，假设后M场中i参加的
有x场，那么最初w=win,l=lose+x，之后每赢一场w++,l--。我们从第i支队伍的点向汇连x条边，
分别代表第i支队伍赢了j场比赛时相对赢j-1场时收益的增量。由于增量一定越来越大（平方嘛），
所以流量最先流过的一定是费用较小的边，即j最小的边。

至此模型完成，答案即所有队伍最初收益+最小费用最大流的费用。

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

char IN;
inline void Int(int &x){
    while(!isdigit(IN=getchar()));
    x = IN-'0';
    while(isdigit(IN=getchar()))
        x = x*10+IN-'0';
}

/******** program ********************/

const int MAXN = 100005;
const int MAXM = 500005;
const ll INF = 1e17;

int pre[MAXN];
ll dis[MAXN];
int po[MAXN],tol;
bool use[MAXN];
int q[MAXM],head,tail;
int vs,vt;
ll ans;
int c[MAXN],d[MAXN],win[MAXN],lose[MAXN],res[MAXN];

struct node{
    int y,f,next;
    ll cost;
}edge[MAXM];

void Add(int x,int y,int f,ll cost){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].cost = cost;
    edge[tol].next = po[x];
    po[x] = tol;
}

void add(int x,int y,int f,ll cost){
    Add(x,y,f,cost);
    Add(y,x,0,-cost);
}

bool spfa(){
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

    int aug = 10000000;
    for(int i=pre[vt];i;i=pre[edge[i^1].y])
        aug = min(aug,edge[i].f);
    for(int i=pre[vt];i;i=pre[edge[i^1].y]){
        edge[i].f -= aug;
        edge[i^1].f += aug;
    }
    ans += ll(dis[vt])*aug;
    return true;
}

inline ll cc(int x,int y,int c,int d){
    return 2LL*c*x-2LL*d*y+c+d;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int n,m;
    while(~RD2(n,m)){
        ans = 0;
        rep1(i,n){
            //RD4(win[i],lose[i],c[i],d[i]);
            Int(win[i]);Int(lose[i]);Int(c[i]);Int(d[i]);
            ans += ll(win[i])*win[i]*c[i];
        }
        Clear(res);
        int x,y;

        Clear(po);
        tol = 1;
        vs = MAXN-3;
        vt = vs+1;

        rep1(i,m){
            //RD2(x,y);
            Int(x);Int(y);
            res[x] ++;
            res[y] ++;
            add(i+n,vt,1,0);
            add(x,i+n,1,0);
            add(y,i+n,1,0);
        }

        rep1(i,n){
            lose[i] += res[i];
            ans += ll(lose[i])*lose[i]*d[i];
            rep(j,res[i])
                add( vs,i,1,cc(win[i]+j,lose[i]-j,c[i],d[i]) );
        }

        while(m--&&spfa())
            ;
        cout<<ans<<endl;
    }

    return 0;
}
