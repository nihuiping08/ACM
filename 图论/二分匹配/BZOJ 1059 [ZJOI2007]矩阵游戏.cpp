/*

由於每個顏色為1的方格只能夠滿足一個x或者y座標，所以可以直接對於i,j建邊，
跑一次最大二分匹配，若存在完美匹配則存在解

*/
#include <set>
#include <map>
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

#define lx(x) (x<<1)
#define rx(x) (x<<1|1)
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

/******** program ********************/

const int MAXN = 202;

bool use[MAXN],Map[MAXN][MAXN];
int ym[MAXN],n;

bool dfs(int x){
    rep1(y,n){
        if(Map[x][y]&&!use[y]){
            use[y] = true;
            if(!ym[y]||dfs(ym[y])){
                ym[y] = x;
                return true;
            }
        }
    }
    return false;
}

void solve(){
    memset(ym,0,sizeof(ym));
    int ans = 0;
    rep1(i,n){
        memset(use,false,sizeof(use));
        if(dfs(i))
            ans ++;
    }
    //cout<<ans<<" "<<n<<endl;
    ans == n?puts("Yes"):puts("No");
}

void init(){
    memset(Map,false,sizeof(Map));
    RD(n);
    int x;
    rep1(i,n){
        rep1(j,n){
            RD(x);
            if(x)
                Map[i][j] = true;
        }
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    while(ncase--){
        init();
        solve();
    }

	return 0;
}
