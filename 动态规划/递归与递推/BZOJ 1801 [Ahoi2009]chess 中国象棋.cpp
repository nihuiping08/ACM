/*

题目:n*m方格矩阵中安放炮，问有多少种放置方式使得没有炮相互攻击
分析：三维dp
    dp[i][x][y]表示前i行放置了x列1个的炮，放置了y列2个的炮
    然后转移方程为：见代码

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

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)

const int MOD = 9999973;
const int MAXN = 102;

ll dp[MAXN][MAXN][MAXN];
int n,m;

ll C(ll x){
    return x*(x-1)>>1;
}

int main(){

#ifndef ONLINE_JUDGE
  freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD2(n,m);

    dp[0][0][0] = 1;
    for(int i=1;i<=n;i++){
        for(int x=0;x<=m;x++){
            for(int y=0;y<=m-x;y++){

                dp[i][x][y] = dp[i-1][x][y]; // put 0

if(x)           dp[i][x][y] += dp[i-1][x-1][y]*(m-x-y+1);// put 1
if(y&&x<m)      dp[i][x][y] += dp[i-1][x+1][y-1]*(x+1);

                // 都放在空列上
if(x>1)         dp[i][x][y] += dp[i-1][x-2][y]*C(m-x-y+2);
                //放置一个在空列上，一个在已经放置了1个的列上
                //注意由于放置了一个1，有从0中补回，所以中间为x
if(x&&y)        dp[i][x][y] += dp[i-1][x][y-1]*(m-x-y+1)*;
                //都放在已经放置了一个的列上
if(y>1&&x<=m-2) dp[i][x][y] += dp[i-1][x+2][y-2]*C(x+2);

                dp[i][x][y] %= MOD;
            }
        }
    }

    ll ans = 0;

    for(int j=0;j<=m;j++)
        for(int k=0;k<=m-j;k++)
            ans += dp[n][j][k];

    cout<<ans%MOD<<endl;

	return 0;
}
