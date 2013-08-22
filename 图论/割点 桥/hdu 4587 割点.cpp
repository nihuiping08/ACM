/*

题目：删除两个点之后使得剩余连通块数量最多。

分析：枚举一个删除点，然后求一遍割点，我们知道如果有割点的话，剩下的一个删除点必然是割点更优。
	因此我们可以根据low值判断一个点删除后拥有多少个不同连通块


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

struct node{
    int y,next;
}edge[MAXN];
int po[MAXN],tol;
int low[MAXN],dfn[MAXN],dep;
bool bad[MAXN];
int n,m;

void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

int ans;
void dfs(int x,int fa){
    low[x] = dfn[x] = ++ dep;
    int tt = 0;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(bad[y])continue;
        if(y==fa)continue;
        if(!dfn[y]){
            dfs(y,x);
            cmin(low[x],low[y]);
            if(low[y]>=dfn[x])
                tt ++;
        }else
            cmin( low[x],dfn[y] );
    }
    cmax(ans,tt+ (fa!=-1) );
}

bool use[MAXN];
void init(int x){
    use[x] =true;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(use[y] || bad[y])continue;
        init(y);
    }
}

int cc(){
    int bcnt = 0;
    Clear(use);
    rep(i,n)
        if(!bad[i]&&!use[i]){
            bcnt ++;
            init(i);
        }
    bcnt --;

    memset(dfn,0,sizeof(dfn));
    dep = 0;

    ans = 0;
    rep(i,n)
        if(!bad[i]&&!dfn[i])
            dfs(i,-1);

    return ans+bcnt;
}

void solve(){
    int ans = 0;

    rep(i,n){
        bad[i] = true;
        int tmp = cc();
        bad[i] = false;

        cmax(ans,tmp);
    }

    printf("%d\n",ans);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m){
        int x,y;
        Clear(po);
        tol = 0;
        while(m--){
            RD2(x,y);
            add(x,y);
            add(y,x);
        }
        Clear(bad);
        //cout<<"wei  "<<cc()<<endl;

        solve();
    }

	return 0;
}
