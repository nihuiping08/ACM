/*

分析：
　　先令p = sigma( pi )
　　菜品制作的代价正向不太好弄，考虑逆向：
　　每个厨师拆成p个点，对于每种菜i由厨师j来做，第一个点表示最后一次做的菜，代价为t[i,j]，
	第二个点表示倒数第二次做，他的代价为2*t[i,j]（最后一个人跟倒数第二个人都需要等待
	该时间）。。。
　　这样建图是对的，但是由于数据范围建立出的图太大而导致TLE。
　　考虑动态建边。
　　第一次时，直接对每种菜品i对每个厨师j建边，表示该厨师最后一道菜是该菜品，费用
	即为t[i,j]。
　　每增广一次，考虑是哪个厨师做的，再对所有菜品跟该厨师连边，继续增广。
　　增广p次之后即为答案。

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


const int MAXN = 1e5+5;
const int MAXM = 1e6+5;
const int INF = 1e9;

int pre[MAXN],dis[MAXN];
int po[MAXN],tol;
bool use[MAXN];
int q[MAXM],head,tail;
int n,m,vs,vt,ans;
int tim[102][102],tot;
int vec[102][1002],top[102],id;

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

inline int spfa(){
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
        return -1;

    int aug = INF;
    for(int i=pre[vt];i;i=pre[edge[i^1].y])
        aug = min(aug,edge[i].f);
    for(int i=pre[vt];i;i=pre[edge[i^1].y]){
        edge[i].f -= aug;
        edge[i^1].f += aug;
    }
    ans += dis[vt]*aug;
    return edge[ pre[vt]^1 ].y;
}

inline void adjust(int now){ // 调整
    rep1(j,m){
        if(vec[j][top[j]]==now){
            vec[j][++top[j]] = ++id;
            add(id,vt,1,0);
            rep1(i,n)
                add(i,id,1,tim[i][j]*top[j] );
            return;
        }
    }
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    while(~RD2(n,m)){
        Clear(po);
        tol = 1;
        vs = MAXN-3;
        vt = vs+1;
        tot = 0;

        int x;
        rep1(i,n){
            RD(x);
            add(vs,i,x,0); // 跟源点相连
            tot += x; // sigma(p)
        }

        Clear(top);
        id = n;

        rep1(j,m){
            vec[j][++top[j]] = ++ id; // 动态分配编号
            add(vec[j][1],vt,1,0);  // 连汇点
        }

        rep1(i,n)
            rep1(j,m){
                RD(tim[i][j]);
                add(i,vec[j][1],1,tim[i][j]);
            }

        ans = 0;
        rep1(k,tot){ // 增广tot次
            int now = spfa();
            adjust(now);
        }
        cout<<ans<<endl;
    }

    return 0;
}
