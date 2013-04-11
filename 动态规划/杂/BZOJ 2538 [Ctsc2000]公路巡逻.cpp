/*

分析：
    令 dp[i][j]表示在第j分鐘到達第i個關口遇到的最少巡邏車，不難想到
    轉移方程如下：
    dp[i][j] = min{ dp[i-1][j-k]+cc(i-1,j-k,j) }
    cc(i-1,j-k,j)表示目標車在 第j-k分鐘從關口i-1在第j分鐘開到關口i所遇
    到的巡邏車次數。
    不算cc函數的話，時間複雜度為 O( n*n*m*m )

    計算cc函數的時候:
    方法一：
    計算從i-1出發到達i的巡邏車的相遇情況。
    時間均攤的話，為O(1+m/n)
    總時間複雜度為 O(n*m^3)
    實際的測試：用了vector為9592 ms，如果不用的話，大概為5~6s

    方法二：
    具體看黑書

*/
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

const int MAXN = 302;

vector<int> s[MAXN],e[MAXN];
int low[MAXN],up[MAXN];
int dp[55][30005];

int cal(int x){
    return x/10000*3600 + x/100%100*60 + x%100;
}

int cc(int pos,int x,int y){
    int ans = 0;
    foreach(i,s[pos]){
        if(s[pos][i]==x)
            ans += e[pos][i]==y;
        else
            ans += (s[pos][i]<x&&e[pos][i]>=y)||(s[pos][i]>x&&e[pos][i]<=y);
    }
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,m;
    int x,y,z;
    RD2(n,m);
    rep(i,m){
        RD3(z,x,y);
        x = cal(x)-6*3600;
        s[z].pb(x);
        e[z].pb(x+y);
    }

    for(int i=2;i<=n;i++){
        low[i] = low[i-1]+300;
        up[i] = up[i-1]+600;
    }

    memset(dp,0x4f,sizeof(dp));
    int ans = dp[0][0];

    dp[1][0] = 0;
    REP(i,2,n)
        REP(j,low[i],up[i])
            for(int k=300;k<=600&&k<=j;k++)
                dp[i][j] = min( dp[i][j],dp[i-1][j-k]+cc(i-1,j-k,j) );

    int pos = 0;
    for(int i=low[n];i<=up[n];i++)
        if(dp[n][i]<ans)
            ans = dp[n][ pos = i ];

    pos += 3600*6;
    cout<<ans<<endl;
    printf("%02d%02d%02d\n",pos/3600,pos%3600/60,pos%60);

	return 0;
}
