/*

题目：给出n个项目，每个项目的开始时间为s，需要时间d完成，完成时得到的奖励为c。
问有m个人做，最大获利多少。

分析：
1.普通做法：
	直接拆点，对于满足条件的建边，求一边最小费用流，但是题目数据比较大，显然会TLE
2.正解：
	对于开始时间以及完成时间进行离散化成k个不同的点，每个点与相邻的点建边。
	对于n个项目，找出开始时间以及完成时间的位置，建边，费用为 -c。
	增广m次，求最小费用流。


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
const int MAXM = 1000005;
const int INF = 1e9;

int pre[MAXN],dis[MAXN];
int po[MAXN],tol;
bool use[MAXN];
int q[MAXM],head,tail;
int vs,vt,ans;

struct node{
    int y,f,cost,next,id;
}edge[MAXM];

void Add(int x,int y,int f,int cost,int id){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].cost = cost;
    edge[tol].id = id;
    edge[tol].next = po[x];
    po[x] = tol;
}

void add(int x,int y,int f,int cost,int id){
    Add(x,y,f,cost,id);
    Add(y,x,0,-cost,id);
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

struct P{
    int s,d,c;
}p[MAXN];

int is[MAXN];
int len[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,m;
    while(cin>>n>>m){
        int tot = 0;
        rep1(i,n){
            RD3(p[i].s,p[i].d,p[i].c);
            p[i].d += p[i].s;

            len[tot++] = p[i].s;
            len[tot++] = p[i].d;
        }

        sort(len,len+tot);
        int tt = unique(len,len+tot)-len;
        tot = tt;

        Clear(po);
        tol = 1;

        vs = 1;
        vt = tot;

        rep1(i,n){
            int x = lower_bound(len,len+tot,p[i].s)-len+1;
            int y = lower_bound(len,len+tot,p[i].d)-len+1;
            add(x,y,1,-p[i].c,i);
        }
        REP(i,2,tot)
            add(i-1,i,m,0,0);

        ans = 0;
        while(m--)
            spfa();

        Clear(is);
        for(int i=2;i<=tol;i+=2)
            if(edge[i].f==0)
                is[ edge[i].id ] = is[ edge[i^1].id ] = true;

        rep1(i,n)
            printf("%d ",is[i]);
        cout<<endl;


        //cout<<"min_cost  =  "<<-ans<<endl;
    }

	return 0;
}
