/*

題目：
    n個男孩m個女孩坐在一起，任意連續的一段男女人數不能夠相差超過K人。
    問一共有多少種排法

分析：
    dp[i][j][x][y]
    表示位置i已經安放了j個男孩，並且之前最大的連續男孩個數為x，最大的
    連續女孩個數為y的安排方案數。
    則轉移方程如下：
	注意需要利用滾動數組。

*/
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

/******** program ********************/

const int MOD = 12345678;

int dp[2][302][21][21];
int n,m,kk;

void add(int &x,int y){
    x += y;
    x %= MOD;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD3(n,m,kk)){
        memset(dp,0,sizeof(dp));
        int old = 1,now = 0;
        dp[0][0][0][0] = 1;

        rep(i,n+m){
            swap(now,old);
            memset(dp[now],0,sizeof(dp[now]));
            rep(j,min(i,n)+1){
                rep(x,min(j,kk)+1){
                    rep(y,min(i-j,kk)+1){
                        int tmp = dp[old][j][x][y];
                        if(j<n&&x<kk)
                            add(dp[now][j+1][x+1][max(y-1,0)],tmp);
                        if(i-j<m&&y<kk)
                            add(dp[now][j][max(x-1,0)][y+1],tmp);
                    }
                }
            }
        }

        int ans = 0;
        kk ++;
        rep(i,kk)
            rep(j,kk)
                add(ans,dp[now][n][i][j]);
        cout<<ans<<endl;
    }

	return 0;
}
