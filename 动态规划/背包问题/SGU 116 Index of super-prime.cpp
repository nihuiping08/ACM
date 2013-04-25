/*

題目：簡單的背包轉移

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

const int MAXN = 20005;
const int INF = 1e9;

bool use[MAXN],ok;
vector<int> prime,a,out;
int dp[MAXN];
int pre[MAXN],qq[MAXN];

void init(){
    use[0] = 1;
    use[1] = 1;
    prime.pb(0);
    for(int i=2;i<MAXN;i++)
        if(!use[i]){
            prime.pb(i);
            for(int j=i+i;j<MAXN;j+=i)
                use[j] = true;
        }
    int len = prime.size()-1;
    rep1(i,len){
        if(use[i])continue;
        a.pb(prime[i]);
    }
}

void dfs(int n){
    if(pre[n])
        dfs(pre[n]);
    if(qq[n])
        out.pb(qq[n]);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    init();
    int n;
    RD(n);
    fill(dp+1,dp+n+1,INF);
    dp[0] = 0;

    rep1(i,n){
        for(int j=0;a[j]<=i;j++){
            if(dp[i]>dp[ i-a[j] ]+1){
                dp[i] = dp[ i-a[j] ]+1;
                qq[i] = a[j];
                pre[i] = i-a[j];
            }
        }
    }

    if(dp[n]!=INF){
        cout<<dp[n]<<endl;
        dfs(n);
        //sort(out.begin(),out.end());
        foreach(i,out){
            if(i)putchar(' ');
            printf("%d",out[i]);
        }
        puts("");
    }
    else
        puts("0");
	return 0;
}
