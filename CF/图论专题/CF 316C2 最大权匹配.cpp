/*

题目：给出n*m的方格，每个方格中放有数，且恰好有n*m/2对，问最少需要交换多少对数，使得方格中任意两
个相邻的格子的数相等。
分析：对于i+j为奇数的格子，连上源点，否则连上汇点。
	对于相邻的格子，颜色不同的话，费用为1，否则费用为0。
	跑一次最小费用流即为答案。
	
	这里求出的最小费用流实际上是每一个格子均有流量流过，如果没找到匹配的话，费用为1，表示两者最少
	需要交换一个。对于其他的也是如此。

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
const int MAXM = 100005;
const int INF = 1e9;

int a[100][100];
int pre[MAXN],dis[MAXN];
int po[MAXN],tol;
bool use[MAXN];
int q[MAXM],head,tail;
int n,m,vs,vt,ans;

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

int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};

int id(int x,int y){
    return x*m-m+y;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m){
        vs = n*m+1;
        vt = vs+1;
        Clear(po);
        tol = 1;
        rep1(i,n)
            rep1(j,m)
                RD(a[i][j]);
        rep1(i,n)
            rep1(j,m){
                if( (i+j)&1 )
                    add(vs,id(i,j),1,0);
                else
                    add(id(i,j),vt,1,0);

                rep(d,4){
                    int x = dx[d]+i;
                    int y = dy[d]+j;
                    if(x&&y&&x<=n&&y<=m){
                        if( (i+j)&1 )
                            add(id(i,j),id(x,y),1,a[i][j]!=a[x][y]);
                        else
                            add(id(x,y),id(i,j),1,a[i][j]!=a[x][y]);
                    }
                }
            }
        ans = 0;
        while(spfa());
        cout<<ans<<endl;
    }

	return 0;
}
