/*

求从根出发的最长有向链

DFS，记录一下每个儿子节点的最大值。

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
#define fir first
#define sec second

/******** program ********************/

const int MAXN = 2e5+5;

int po[MAXN],tol;
int dp[MAXN];

struct node{
    int y,w,next;
}edge[MAXN];

void add(int x,int y,int w){
    edge[++tol].y = y;
    edge[tol].w = w;
    edge[tol].next = po[x];
    po[x] = tol;
}

int dfs(int x,int fa){
    int sum = 0;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)continue;
        sum = max(sum,dfs(y,x)+edge[i].w);
    }
    return sum;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n;
    while(cin>>n){
        memset(po,0,sizeof(po));
        tol = 0;
        int x,y,w;
        ll ans = 0;
        REP(i,2,n){
            RD3(x,y,w);
            add(x,y,w);
            add(y,x,w);
            ans += w;
        }
        ans <<= 1;
        cout<<ans-dfs(1,0)<<endl;
    }

	return 0;
}
