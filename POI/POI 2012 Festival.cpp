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
#define fir first
#define sec second
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/

const int MAXN = 1005;
const int MAXM = 2e5+5;
const int INF = 1000000000;

int po[MAXN],tol;
int dis[MAXN][MAXN];
int dfn[MAXN],low[MAXN],fa[MAXN],sta[MAXN],bcnt,dep,top;
bool use[MAXN];
int n,m1,m2;

struct node{
    int y,val,next;
}edge[MAXM];

void dfs(int x){
    use[x] = true;
    sta[++top] = x;
    low[x] = dfn[x] = ++dep;

    int y;
    for(int i=po[x];i;i=edge[i].next){
        y = edge[i].y;
        if(!dfn[y]){
            dfs(y);
            low[x] = min(low[x],low[y]);
        }else if(use[y])
            low[x] = min(low[x],dfn[y]);
    }

    if(low[x]==dfn[x]){
        ++ bcnt;
        do{
            y = sta[top--];
            use[y] = false;
            fa[y] =bcnt;
        }while(x!=y);
    }
}

void tarjan(){
    memset(use,false,sizeof(use));
    memset(dfn,0,sizeof(dfn));
    top = dep = bcnt = 0;
    rep1(i,n)
        if(!dfn[i])
            dfs(i);
    //cout<<"bcnt = "<<bcnt<<endl;
}

void solve(){
    rep1(i,n)
        rep1(j,n)
            dis[i][j] = (i==j?0:-INF);

    rep1(x,n)
        for(int i=po[x];i;i=edge[i].next){
            int y = edge[i].y;
            if(fa[x]==fa[y])
                dis[x][y] = max( dis[x][y],edge[i].val );
        }

    rep1(k,n)
    rep1(i,n)
    if(dis[i][k]>-INF)
    rep1(j,n)
    if(dis[k][j]>-INF)
    dis[i][j] = max(dis[i][j],dis[i][k]+dis[k][j]);

    rep1(i,n)
        if(dis[i][i]>0){
            puts("NIE");
            return;
        }

    int ans = 0;
    memset(use,false,sizeof(use));
    rep1(i,n){
        if(use[i])continue;
        vector<int> vec;
        int tmp = 0;
        rep1(j,n)
            if(fa[i]==fa[j]){
                use[j] = true;
                vec.pb(j);
            }

        foreach(j,vec)
            foreach(k,vec)
                tmp = max(tmp, abs(dis[ vec[j] ][ vec[k] ])+1 );
        ans += tmp;
    }

    cout<<ans<<endl;
}

void add(int x,int y,int val){
    edge[++tol].y = y;
    edge[tol].val = val;
    edge[tol].next = po[x];
    po[x] = tol;
}

int main(){


    while(cin>>n>>m1>>m2){
        int x,y;

        while(m1--){
            RD2(x,y);
            add(x,y,1);
            add(y,x,-1);
        }
        while(m2--){
            RD2(x,y);
            add(x,y,0);
        }
        tarjan();
        solve();
    }

	return 0;
}
