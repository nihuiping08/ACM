/*

題目：
    一天，郑厂长带着他的军队来到了一个n*m的平原准备布阵。
　　根据以往的战斗经验，每个士兵可以攻击到并且只能攻击到与之曼哈顿距
    离为2的位置以及士兵本身所在的位置。当然，一个士兵不能站在另外一
    个士兵所能攻击到的位置，同时因为地形的原因平原上也不是每一个位置
    都可以安排士兵。
　　现在，已知n,m 以及平原阵地的具体地形，请你帮助郑厂长计算该阵地,
    最多能安排多少个士兵。

分析：
    狀態壓縮DP。
    炮兵陣地的簡單變形。。

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

int dp[102][MAXN][MAXN];
int sta[MAXN],sum[MAXN],top;
int cur[102];
int n,m;

int cal(int x){
    int ans = 0;
    while(x){
        ans += x&1;
        x >>= 1;
    }
    return ans;
}

void init(){
    top = 0;
    int all = 1<<m;
    rep(i,all)
        if( (i&(i<<2))==0 ){
            sta[top] = i;
            sum[top++] = cal(i);
        }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD2(n,m)){
        init();
        memset(dp,-1,sizeof(dp));
        memset(cur,0,sizeof(cur));
        int x;

        rep(i,n)
            rep(j,m){
                RD(x);
                if(!x) cur[i] |= 1<<j;
            }

        rep(i,top)
            if( (sta[i]&cur[0])==0 )
                dp[0][0][i] = sum[i];

        n --;

        rep1(x,n)
            rep(i,top) if( (sta[i]&cur[x])==0 )
                rep(j,top) if( (sta[i]&(sta[j]<<1))==0 && (sta[j]&(sta[i]<<1))==0 )
                    rep(k,top) if( (sta[i]&sta[k])==0 )
                        if(dp[x-1][k][j]!=-1 && (sta[j]&(sta[k]<<1))==0 && (sta[k]&(sta[j]<<1))==0 )
                            dp[x][j][i] = max(dp[x][j][i],dp[x-1][k][j]+sum[i]);

        int ans = 0;
        rep(i,top)
            rep(j,top)
                ans = max(ans,dp[n][i][j]);
        cout<<ans<<endl;
    }

	return 0;
}
