/*

題目：炮兵陣地
分析：
    我第一道的狀態壓縮DP
    我們可以先預處理出每行的合法狀態
    然後預處理出每行的H的安排情況
    dp[x][i][j]表示在第x-1行狀態為i在第x行狀態為j的最大安排數目

    剩下的看代碼吧。

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

const int MAXN = 65;
const int MAXM = 105;

 // 第i行   i-1行狀態 i行狀態
int dp[MAXM][MAXN][MAXN];
// 狀態       狀態i的安排個數 總狀態數
int sta[MAXN],sum[MAXN]  ,    top;
// 第i行山的安排情況
int a[MAXM];
int n,m;

bool ok(int x){
    if(x&(x<<1))    return false;
    if(x&(x<<2))    return false;
    return true;
}

int cal(int x){
    int ans = 0;
    while(x){
        ans += x&1;
        x >>= 1;
    }
    return ans;
}

void init(){
    int all = 1<<m;
    rep(i,all)
        if(ok(i)){
            sta[top] = i;
            sum[top++] = cal(i);
        }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD2(n,m);
    init();
    char str[20];
    rep(i,n){
        scanf("%s",str);
        rep(j,m)
            if(str[j]=='H')
                a[i] |= 1<<j;
    }

    memset(dp,-1,sizeof(dp));
    rep(i,top)
        if( !(sta[i]&a[0]) )
            dp[0][0][i] = sum[i];

    n --;
    rep1(x,n){
        rep(i,top){ // x
            if(a[x]&sta[i])
                continue;
            rep(j,top){ // x-1
                if(sta[i]&sta[j])
                    continue;
                rep(k,top){ // x-2
                    if(sta[i]&sta[k])
                        continue;
                    if(dp[x-1][k][j]==-1)
                        continue;
                    dp[x][j][i] = max(dp[x][j][i],dp[x-1][k][j]+sum[i]);
                }
            }
        }
    }

    int ans = 0;
    rep(i,top)
        rep(j,top)
            ans = max(ans,dp[n][i][j]);
    cout<<ans<<endl;

	return 0;
}
