/*

題目：
    dp[i] = min{ dp[j]+max(x_k)*max(y_k) },j<=k<=i,j<i

分析：
    單調隊列優化DP
    由於上述轉移方程還不滿足單調性，所以我們需要進一步轉化。

    先按x排序，則當j<i時，必有x_j<=x_i。
    若y_j<=y_i，則j矩形可以忽略。
    然後，我們發現，剩餘的矩形是滿足隨x增加y下降。

    所以我們可以得到決策方程如下：
    dp[i] = min{ dp[j]+x[i]*y[j+1] } , j<i
    然後我們假設存在兩個決策點j,k，j<k，並且k點比j點更優，有：
    dp[k]+x[i]*y[k+1]<dp[j]+x[i]*y[j+1]
    得到斜率計算方式。

    然後就可以直接用單調隊列進行優化了

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
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

/******** program ********************/

const int MAXN = 50005;

ll dp[MAXN];
int q[MAXN];

struct node{
    int x,y;
    friend bool operator < (node a,node b){
        return a.x<b.x || (a.x==b.x&&a.y>b.y);
    }
}p[MAXN];

bool G(int k,int j,int x){
    return dp[k]+ll(x)*p[k+1].y <= dp[j]+ll(x)*p[j+1].y;
}

bool S(int k,int j,int k1,int j1){ /// 注意到k>j,p[k].y<p[j].y，所以變號
    return ll(dp[k]-dp[j])*(p[k1+1].y-p[j1+1].y)<=ll(dp[k1]-dp[j1])*(p[k+1].y-p[j+1].y);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n;
    RD(n);
    rep1(i,n)
        RD2(p[i].x,p[i].y);
    sort(p+1,p+n+1);

    int cnt = n;
    n = 0;
    rep1(i,cnt){
        while(n && p[i].y>=p[n].y)
            n --;
        p[++n] = p[i];
    }
    int H = 0,T = 0;
    q[++T] = 0;

    rep1(i,n){
        while(H<T&&G(q[H+1],q[H],p[i].x))
            H ++;
        int j = q[H];
        dp[i] = dp[j]+ll(p[i].x)*p[j+1].y;
        while(H<T&&S(q[T],q[T-1],i,q[T]))
            T --;
        q[++T] = i;
    }
    cout<<dp[n]<<endl;

	return 0;
}
