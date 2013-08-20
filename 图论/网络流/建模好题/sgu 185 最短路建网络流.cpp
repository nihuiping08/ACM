/*

题目：给出一个图，从图中找出两条最短路，使得边不重复。

分析：先求一遍最短路，最短路上的点可以构成一个新图，对于新图求一遍最大流，如果存在大于1的最大流，
则有解。

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
#include <utility>
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


const int MAXN = 405;
const int MAXM = 200005;
const int INF = 1e9;

bool use[MAXN];
int po[MAXN],tol;
int gap[MAXN],dis[MAXN],arc[MAXN],pre[MAXN],cur[MAXN];
int n,m,vs,vt;
int a[MAXN],b[MAXN];

vector< int > vec[MAXN];

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

bool sap(){
    memset(dis,0,sizeof(dis));
    memset(gap,0,sizeof(gap));
    gap[0] = vt;
    rep1(i,vt)
        arc[i] = po[i];

    int ans = 0;
    int aug = INF;
    int x = vs;
    bool ok = false;

    while(dis[vs]<vt){
        ok = false;
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
    //cout<<cnt<<endl;
    return ans>=2;
}

void spfa(){

    rep1(i,n)
        dis[i] = INF;
    Clear(use);
    dis[1] = 0;

    queue<int> q;
    q.push(1);

    while(!q.empty()){
        int x = q.front();
        q.pop();
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            int y = edge[i].y;
            int t = dis[x]+edge[i].f;
            if(dis[y]>t){
                dis[y] = t;
                vec[y].clear();
                vec[y].pb(x);
                if(!use[y]){
                    use[y] = true;
                    q.push(y);
                }
            }else if(dis[y]==t)
                vec[y].pb(x);
        }
    }

    Clear(po);
    tol = 1;
    vs = 1;
    vt = n;


    //puts("**********************");
    rep1(x,n)
        foreach(i,vec[x]){
            add( vec[x][i],x,1 );
            //cout<<vec[x][i]<<" "<<x<<endl;
        }
    //puts("**********************");
}

void dfs(int x){
    if(x==1)
        printf("1");
    else
        printf(" %d",x);
    if(x==vt)return;
    for(int i=po[x];i;i=edge[i].next){
        //cout<<edge[i].y<<" "<<edge[i].f<<endl;
        if( edge[i].f==0 && (i&1)==0 ){
            dfs(edge[i].y);
            edge[i].f = 1;
            return;
        }
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    cin>>n>>m;
    int x,y,z;

    Clear(po);
    tol = 0;

    while(m--){
        RD3(x,y,z);
        Add(x,y,z);
        Add(y,x,z);
    }
    spfa();
    bool ok = sap();

    if(ok){
        //puts("YES");

        dfs(vs);
        puts("");

        dfs(vs);
        puts("");

    }else
        puts("No solution");

	return 0;
}
