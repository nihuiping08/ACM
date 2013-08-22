/*

题目：寻找树的重心

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

const int MAXN = 5e4+5;

vector<int> adj[MAXN];
int dmax[MAXN];
int sz[MAXN],n;

int MAX,sum,root;
void dfsRoot(int x,int fa){
    sz[x] = 1;
    dmax[x] = 0;
    foreach(i,adj[x]){
        int y = adj[x][i];
        if(y==fa)continue;
        dfsRoot(y,x);
        sz[x] += sz[y];
        cmax( dmax[x] , sz[y] );
    }
    cmax ( dmax[x] , n-sz[x] );

    if(dmax[x]<MAX){
        root = x;
        sum = 1;
        MAX = dmax[x];
    }else if(dmax[x]==MAX)
        sum ++;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    while(ncase--){
        RD(n);
        rep1(i,n)
            adj[i].clear();
        int x,y;
        REP(i,2,n){
            RD2(x,y);
            adj[x].pb(y);
            adj[y].pb(x);
        }
        MAX = n;
        sum = 1;
        dfsRoot(1,0);
        cout<<root<<" "<<MAX<<endl;
    }

    return 0;
}
