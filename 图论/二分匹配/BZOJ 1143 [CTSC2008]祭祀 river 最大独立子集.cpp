/*

题目：
    图的最大独立子集

*/
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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

const int MAXN = 505;

vector<int> vec[MAXN];
bool map[MAXN][MAXN];
int ym[MAXN],n,m;
bool use[MAXN];

bool dfs(int x){
    rep1(y,n){
        if(map[x][y]&&!use[y]){
            use[y] = true;
            if(ym[y]==-1||dfs(ym[y])){
                ym[y] = x;
                return true;
            }
        }
    }
    return false;
}

void solve(){
    memset(ym,-1,sizeof(ym));
    int ans = 0;
    rep1(i,n){
        memset(use,false,sizeof(use));
        if(dfs(i))
            ans ++;
    }
    cout<<n-ans<<endl;
}

void build(int x){
    use[x] = true;
    foreach(i,vec[x]){
        int y = vec[x][i];
        if(!use[y])
            build(y);
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD2(n,m);
    int x,y;
    while(m--){
        RD2(x,y);
        vec[x].pb(y);
    }
    rep1(i,n){
        memset(use,false,sizeof(use));
        build(i);
        use[i] = false;
        rep1(j,n)
            if(use[j])
                map[i][j] = true;
    }
    solve();

	return 0;
}
