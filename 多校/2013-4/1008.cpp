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
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/

const int MOD = 10007;
const int MAXN = 10090;

char s[MAXN];
int a[MAXN];
int dp[MAXN];

int dfs(int n){
    if(n<2)return dp[n] = 1;
    if(dp[n])return dp[n];
    return dp[n] = (dfs(n-1)+dfs(n-2))%MOD;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    dfs(MAXN-1);

    rep1(Ncase,ncase){
        int ans = 1;
        int now = 0;
        scanf("%s",s);
        for(int i=1;s[i];){
            if(s[i]=='e'&&s[i-1]=='h'){
                now ++;
                i += 2;
            }else{
                i ++;
                ans = ans*dp[now]%MOD;
                now = 0;
            }
        }
        ans = (ans*dp[now])%MOD;
        printf("Case %d: %d\n",Ncase,ans);
    }

	return 0;
}
