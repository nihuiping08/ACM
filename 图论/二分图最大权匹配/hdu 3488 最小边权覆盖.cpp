/*

题目：找一个或多个环使得所有的点被覆盖
分析：画图可知，每个点出发都需要找到另外一个点，并且使得边权最小，恰好是最小边权点覆盖，使用km
	算法即可

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

const int MAXN = 205;
const int INF = 1e9;

int g[MAXN][MAXN];
bool usex[MAXN],usey[MAXN];
int lx[MAXN],ly[MAXN];
int slack[MAXN],ym[MAXN];
int po[MAXN],tol;
int n;

bool dfs(int x){
    usex[x] = true;
    rep1(y,n){
        if(!usey[y]){
            int tmp = lx[x]+ly[y]-g[x][y];
            if(!tmp){
                usey[y] = true;
                if(ym[y]==-1||dfs(ym[y])){
                    ym[y] = x;
                    return true;
                }
            }else
                cmin( slack[y],tmp );
        }
    }
    return false;
}

void km(){
    Clear(ly);
    memset(ym,-1,sizeof(ym));
    rep1(x,n){
        lx[x] = -INF;
        rep1(y,n)
            cmax( lx[x] , g[x][y] );
    }

    rep1(i,n){
        rep1(j,n)
            slack[j] = INF;
        while(true){
            Clear(usex);
            Clear(usey);
            if(dfs(i))
                break;
            int MIN = INF;
            rep1(j,n)
                if(!usey[j])
                    cmin(MIN,slack[j]);
            rep1(j,n)
                if(usex[j])
                    lx[j] -= MIN;
            rep1(j,n){
                if(usey[j])
                    ly[j] += MIN;
                else
                    slack[j] -= MIN;
            }
        }
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase,m,x,y,z;
    RD(ncase);
    while(ncase--){
        RD2(n,m);
        Clear(po);
        tol = 0;
        rep1(i,n)
            rep1(j,n)
                g[i][j] = -INF;
        while(m--){
            RD3(x,y,z);
            cmax( g[x][y],-z );
        }

        km();

        int ans = 0;
        rep1(i,n)
            ans += g[ym[i]][ i ];
        cout<<-ans<<endl;
    }

	return 0;
}
