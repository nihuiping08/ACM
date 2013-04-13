/*

題目：
    在N×N的棋盘里面放K个国王，使他们互不攻击，共有多少种摆放方案。
    国王能攻击到它上下左右，以及左上左下右上右下八个方向上附近的各
    一个格子，共8个格子。
分析：
    簡單狀態壓縮題
    dp [row] [state] [num]表示第row行，狀態為state，目前的安放了num個
    的情況

    由於狀態可能為0，而二進制下1的個數為0，我SB的直接用他的個數來判是否
    可行。調了一晚上。。。

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

const int MAXN = 600;

ll dp[10][80][MAXN];
int sta[MAXN];
bool use[MAXN][MAXN];
int n,num;

int cal(int x){
    int ans = 0;
    while(x){
        ans += (x&1);
        x >>= 1;
    }
    return ans;
}

void init(){
    memset(sta,-1,sizeof(sta));
    int all = 1<<n;
    rep(i,all)
        if( (i&(i<<1))==0 )
            sta[i] = cal(i);

    rep(i,all) if(sta[i]!=-1)
        rep(j,all) if(sta[j]!=-1)
            if( (i&j)==0 && (i&(j>>1))==0 && (j&(i>>1))==0 )
                use[i][j] = true;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD2(n,num);
    init();

    int all = 1<<n;

    rep(i,all)
        if(sta[i]!=-1)
            dp[0][sta[i]][i] = 1;

    n --;
    rep1(x,n)
        rep(i,all) if(sta[i]!=-1)
            rep(j,all) if(sta[j]!=-1)
                if( use[i][j] )
                    for(int k=sta[j];k+sta[i]<=num;k++)
                        dp[x][ k+sta[i] ][i] += dp[x-1][k][j];
    ll ans = 0;
    rep(i,all)
        if(sta[i]!=-1)
            ans += dp[n][num][i];
    cout<<ans<<endl;

	return 0;
}
