/*

极大极小博弈dp

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
#define lson rt<<1
#define rson rt<<1|1

/******** program ********************/

bool g[17][17];
int hax[13],hay[13];
int dp[1<<12];
int n,ncase,tot;

void init(){
    tot = 0;
    for(int i=0;i<=12;i+=4)
        for(int j=1;j<4;j++){
            int x = i+j;
            if(g[x][x+1]==0){
                hax[tot] = x;
                hay[tot] = x+1;
                tot ++;
            }
        }
    for(int j=1;j<=4;j++)
        for(int i=0;i<=8;i+=4){
            int x = i+j;
            if(g[x][x+4]==0){
                hax[tot] = x;
                hay[tot] = x+4;
                tot ++;
            }
        }
}

int cc(int x,int y){
    int ans = 0;
    if(x+1==y){
        ans += x>4&&g[x-4][x]&&g[x-4][x-3]&&g[x-3][x+1];
        ans += x<13&&g[x][x+4]&&g[x+4][x+5]&&g[x+1][x+5];
    }else{
        ans += (x%4!=1)&&g[x-1][x]&&g[x-1][x+3]&&g[x+3][x+4];
        ans += (x%4!=0)&&g[x][x+1]&&g[x+1][x+5]&&g[x+4][x+5];
    }
    return ans;
}

int dfs(int sta,int last){
    if(~dp[sta])return dp[sta];
    if(last==0)return dp[sta] = 0;
    int ans = 0;
    for(int i=0;i<tot;i++){
        if( sta>>i & 1 )continue;
        int x = hax[i] , y = hay[i];
        g[x][y] = g[y][x] = 1;
        int res = last-dfs( sta|(1<<i) , last-cc(x,y) );
        cmax(ans,res);
        g[x][y] = g[y][x] = 0;
    }
    return dp[sta] = ans;
}

bool solve(int x,int y){
    if(x>4)return 1;
    int last = 9-x-y;
    memset(dp,-1,sizeof(dp));
    int a = dfs(0,last);
    int b = last-a;
    if(n&1)swap(a,b);
    return a+x>b+y;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int x,y,Ncase = 0;
    RD(ncase);
    while(ncase--){
        int a = 0 , b = 0;
        RD(n);
        Clear(g);
        rep1(i,n){
            RD2(x,y);
            if(x>y)swap(x,y);
            g[x][y] = g[y][x] = 1;
            if(i&1)a += cc(x,y);
            else b += cc(x,y);
        }
        init();
        printf("Case #%d: %s\n",++Ncase,solve(a,b)?"Tom200":"Jerry404");
    }

    return 0;
}
