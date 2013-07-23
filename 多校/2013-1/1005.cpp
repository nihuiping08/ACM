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

/******** program ********************/

const int MAXN = 100005;

int dp[MAXN];
int da[MAXN],dc[MAXN];
int a[MAXN],n;
int q[MAXN*5];
int id[MAXN*5];

void LIS(){
    int top = 0;
    dp[++top] = a[n];
    da[n] = 1;
    for(int i=n-1;i;i--){
        if(a[i]>=dp[top]){
            dp[++top] = a[i];
            da[i] = top;
        }else{
            int l = 1;
            int r = top;
            int ans = 0;
            while(l<=r){
                int mid = (l+r)/2;
                if(dp[mid]>a[i]){
                    ans = mid;
                    r = mid-1;
                }else
                    l = mid+1;
            }
            dp[ans] = a[i];
            da[i] = ans;
        }
    }
}

void DEC(){
    int top = 0;
    dp[++top] = a[n];
    dc[n] = 1;
    for(int i=n-1;i;i--){
        if(a[i]<=dp[top]){
            dp[++top] = a[i];
            dc[i] = top;
        }else{
            int l = 1;
            int r = top;
            int ans = 0;
            while(l<=r){
                int mid = (l+r)/2;
                if(dp[mid]<a[i]){
                    ans = mid;
                    r = mid-1;
                }else
                    l = mid+1;
            }
            dp[ans] = a[i];
            dc[i] = ans;
        }
    }
}

void solve(){
    int ans = 0;
    rep1(i,n)
        cmax(ans,dc[i]+da[i]-1);
    cout<<ans<<endl;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    while(ncase--){
        RD(n);
        rep1(i,n)
            RD(a[i]);
        LIS();
        DEC();

        /*
        rep1(i,n)
            printf("%d ",da[i]);
        puts("");
        rep1(i,n)
            printf("%d ",dc[i]);
        puts("");
        */

        solve();
    }

	return 0;
}
