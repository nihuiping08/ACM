/*

題目：
    有50斤的人c1人，100斤的人c2人。現在他們需要過河，但是只有一條船，並且船的載重重量不超過k。問有多少種方法
	使得運人過河的次數最少。

分析：
    三維DP。
    由於從河的對岸過來以及過去河的對岸是等價的，所以我們直接考慮單次過河的情況。
    dp[i][x][y]表示第i次過河，過河之後對岸有50斤的人x，100斤的人y的方法數。
    
	我們假設第n次過河的人的個數為i,j，過河前河岸有x,y人，所以過完河之後河的對岸有c1-x+i,c2-y+j人。
	所以轉移方程為
	dp[n][c1-x+i][c2-y+j] += dp[n-1][x][y]*comb[x][i]*comb[y][j];
	comb[x][y]表示從x人裏面選擇y個人過河的組合數。
	
	需要注意每次過河的人數必須大於0並且不能夠超載。
	運算過程中需要模1e9+7以防爆long long。
	另外我們可以用滾動數組來減少內存。
	運輸的最大次數不能夠超過n次，否則無解。
	
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

const int MOD = 1e9+7;
const int MAXN = 51;

ll comb[MAXN][MAXN],dp[2][MAXN][MAXN];
int c1,c2,n,num,old,now;

void solve(){
    swap(now,old);
    memset(dp[now],0,sizeof(dp[now]));

    rep(i,c1+1) /// 當前有i,j人過河
        rep(j,c2+1) if( (i+j*2) && i+j*2<=num ) /// 有人過河並且過河的人的重要不能夠超過載重
            REP(x,i,c1) /// 河岸有x,y人，我們可以算出河的對岸有多少人
                REP(y,j,c2)
                    dp[now][c1-x+i][c2-y+j] += dp[old][x][y]*comb[x][i]%MOD*comb[y][j]%MOD;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    rep(i,51){
        comb[i][0] = 1;
        rep1(j,i)
            comb[i][j] = (comb[i-1][j]+comb[i-1][j-1])%MOD;
    }

    while(~RD2(n,num)){
        num /= 50;

        int x;
        c1 = c2 = 0;
        rep(i,n){
            RD(x);
            c1 += x==50;
            c2 += x==100;
        }

        memset(dp,0,sizeof(dp));
        old = 1,now = 0;
        dp[now][c1][c2] = 1;
        bool ok = false;

        rep(i,n){
            solve();
            if(dp[now][c1][c2]){
                cout<<i*2+1<<endl;
                cout<<dp[now][c1][c2]%MOD<<endl;
                ok = true;
                break;
            }
            solve();
        }
        if(!ok)
            puts("-1\n0");
    }

	return 0;
}
