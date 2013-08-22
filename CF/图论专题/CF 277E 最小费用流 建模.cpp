/*

题目：给出平面上n个点，现在对这n个点建立一棵二叉树，满足父节点的纵坐标大于儿子节点。
建边的费用为欧几里得距离，问最少费用。

分析：
建图时：
	需要约束每个点只能往外引两条边，所以需要把原来的点拆成两个，一个点 i 连源点，流量为2。
	另一个点 i' 连汇点，流量为1。
	对于纵坐标高的点 i 向低的点 j' 引一条边，流量为1，表示可以建一条边。费用为欧几里得距离。
	
	求一次最小费用流


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


const int MAXN = 10005;
const int MAXM = 500005;
const int INF = 1e9;

int pre[MAXN];
double dis[MAXN];
int po[MAXN],tol;
bool use[MAXN];
int q[MAXM],head,tail;
int n,m,vs,vt;
double ans;
int flow;

struct node{
    int y,f,next;
    double cost;
}edge[MAXM];

void Add(int x,int y,int f,double cost){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].cost = cost;
    edge[tol].next = po[x];
    po[x] = tol;
}

void add(int x,int y,int f,double cost){
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

PII p[MAXN];

double cal(double x,double y){
    return sqrt(x*x+y*y);
}

double cal(PII a,PII b){
    return cal(a.first-b.first,a.second-b.second);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n){
        Clear(po);
        tol = 1;
        rep1(i,n)
            RD2(p[i].second,p[i].first);

        sort(p+1,p+n+1);
        reverse(p+1,p+n+1);

        vs = n<<1|1;
        vt = vs+1;

        rep1(i,n){
            add(vs,i,2,0);
            add(i+n,vt,1,0);
            REP(j,i+1,n)
                if(p[i].first>p[j].first)
                    add(i,j+n,1,cal(p[i],p[j]));
        }

        flow = 0;
        ans = 0;
        while(spfa())
            ;

        for(int i=po[vt];i;i=edge[i].next)
            if(edge[i].f>0)
                flow += edge[i].f;

        if(flow+1==n)
            printf("%.12lf\n",ans);
        else
            puts("-1");
    }

	return 0;
}
