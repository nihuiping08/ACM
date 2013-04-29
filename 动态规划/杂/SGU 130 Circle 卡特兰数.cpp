/*

題目：圓周上n割點，問有多少種方式可以把圓分割成最少的塊
分析：dp
    dp[i]表示有i個點的分割方式
    顯然dp[i] = sigma( dp[j]*dp[i-j-1] )

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

ll dp[62];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n;
    while(cin>>n){
        memset(dp,0,sizeof(dp));
        dp[0] = dp[1] = 1;
        for(int i=2;i<=n;i++)
            for(int j=0;j<i;j++)
                dp[i] += dp[j]*dp[i-j-1];
        cout<<dp[n]<<" "<<n+1<<endl;
    }

	return 0;
}
