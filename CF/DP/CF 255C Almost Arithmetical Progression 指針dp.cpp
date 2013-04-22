/*

題目：
    找出子串，使得子串為abab...型 且長度最大

分析：
    dp
    dp[i][j]表示以i元素a_i開始，由a_j結束的最優解
    則轉移的時候
    dp[i][j] = dp[ j ][ now ]+1;
    now為比j位置大並且符合 abab 型
    我們假設i為a，j為b。我們需要找下一個a的位置now。
    顯然可以用后向星來標記

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

const int MAXN = 4002;
const int MAXM = 1e6+5;

int po[MAXN],nx[MAXM],a[MAXN],dp[MAXN][MAXN],n;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD(n)){
        rep1(i,n)
            RD(a[i]);
        if(n<3){
            cout<<n<<endl;
            continue;
        }

        memset(po,0,sizeof(po));
        memset(dp,0,sizeof(dp));
        memset(nx,0,sizeof(nx));

        int ans = 0;
        for(int i=n;i;i--){
            int now = nx[a[i]];
            dp[i][i] = 1;
            for(int j=i+1;j<=n;j++){
                while( now && j>=now ) // 找到下一個a的位置並且a的位置比j大
                    now = po[now];
                if(now) // 有的話
                    dp[i][j] = dp[j][now]+1;
                else // 沒有的話
                    dp[i][j] = 2;
                //cout<<i<<" "<<j<<" now =  "<<now<<" "<<dp[i][j]<<endl;
                ans = max(ans,dp[i][j]);
            }
            po[i] = nx[a[i]];
            nx[a[i]] = i;
        }
        cout<<ans<<endl;
    }

	return 0;
}
