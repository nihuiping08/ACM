/*

题目：
	给出一个闭区间[a,b]中的全部整数，如果其中某两个数x,y（设x>y）的平方差x2-y2是一个完全平方数z2，
	并且y与z互质，那么就可以将x和y连起来并且将它们一起消除，同时得到x+y点分数。

分析：
	二分最大权匹配，首先对于每个点拆点，x,x'
	对于可行的x,y连边 x'y , yx' ，费用均为-x-f，求一次最小费用流
	
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
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/

const int MAXN = 10005;
const int MAXM = 1000005;
const int INF = 1e9;

int pre[MAXN],dis[MAXN];
int po[MAXN],tol;
bool use[MAXN];
int q[MAXM],head,tail;
int n,m,s,t,ans;
map<int,int> sqr;
int flow;

struct node{
    int y,f,cost,next;
}edge[MAXM];

void Add(int x,int y,int f,int cost){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].cost = cost;
    edge[tol].next = po[x];
    po[x] = tol;
}

void add(int x,int y,int f,int cost){
    Add(x,y,f,cost);
    Add(y,x,0,-cost);
}

bool spfa(){
    memset(use,false,sizeof(use));
    rep1(i,t)
        dis[i] = INF;
    dis[s] = 0;
    head = tail = 0;
    q[tail++] = s;
    pre[s] = 0;
    while(head<tail){
        int x = q[head++];
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            int y = edge[i].y;
            int now = edge[i].cost+dis[x];
            if(edge[i].f>0&&dis[y]>now){
                dis[y] = now;
                pre[y] = i;
                if(!use[y]){
                    use[y] = true;
                    q[tail++] = y;
                }
            }
        }
    }
    if(dis[t]==INF)
        return false;

    int aug = INF;
    for(int i=pre[t];i;i=pre[edge[i^1].y])
        aug = min(aug,edge[i].f);
    for(int i=pre[t];i;i=pre[edge[i^1].y]){
        edge[i].f -= aug;
        edge[i^1].f += aug;
    }
    ans += dis[t]*aug;
    return true;
}

int gcd(int a,int b){
    return a?gcd(b%a,a):b;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    rep1(i,MAXN)
        sqr[i*i] = i;
    int a,b;
    while(cin>>a>>b){
        memset(po,0,sizeof(po));
        tol = 1;

        s = b<<1|1;
        t = s+1;

        REP(y,a,b){
            REP(x,y+1,b){
                int z = sqr[ x*x-y*y ];
                if(z&&gcd(y,z)==1){
                    add( x,y+b,1,-x-y );
                    add( y,x+b,1,-x-y );
                }
            }
            add( y,y+b,1,0 );
            add( y+b,t,1,0 );
            add( s,y,1,0 );
            add( y,t,1,0 );
        }

        ans = 0;
        while(spfa())
            ;
        flow = 0;
        for(int i=po[t];i;i=edge[i].next)
            if(edge[i].y>b&&edge[i].f>0)
                flow ++;
        cmax(ans,-ans);
        cout<<flow/2<<" "<<ans/2<<endl;
    }

	return 0;
}
