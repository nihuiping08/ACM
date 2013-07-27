/*

判断图是否连通并且只有一个环

记录时间戳。

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

const int MAXN = 105;

bool g[MAXN][MAXN],use[MAXN];
int n,m,cnt;

void dfs(int x,int fa){
    use[x] = true;
    //cout<<x<<" ";
    rep1(i,n){
        if(i==fa||!g[x][i])continue;
        if(use[i]){
            cnt ++;
            //cout<<"i = "<<i<<" "<<x<<endl;
        }
        else        dfs(i,x);
    }
}

bool solve(){
    memset(use,false,sizeof(use));
    bool ok = false;
    cnt = 0;
    rep1(i,n)
        if(!use[i]){
            if(ok)return false;
            ok = true;
            dfs(i,0);
        }
    //cout<<"\n cnt = "<<cnt<<endl;
    return cnt==2;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int x,y;
    while(cin>>n>>m){
        memset(g,0,sizeof(g));
        while(m--){
            RD2(x,y);
            g[x][y] = g[y][x] = true;
        }
        if(solve())
            puts("FHTAGN!");
        else
            puts("NO");
    }

	return 0;
}
