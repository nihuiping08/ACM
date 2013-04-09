/*

題目：
    切割矩形，使得標準差最小。
分析：
    a,b,n<=10，可以五維DP進行記憶化搜索來做。
    dp[i][j][x][y][num]表示矩形[(i,j),(x,y)]內需要切割num下的最優解。
    dfs切割的方式

*/
#include <cmath>
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

const int N = 11;
const double INF = 1e50;

double dp[N][N][N][N][N];
double map[N][N],sum[N][N],ave;
int n,m,d;

double sqr(double x){
    return x*x;
}

double dfs(int x1,int y1,int x2,int y2,int num){
    if(dp[x1][y1][x2][y2][num]<INF)
        return dp[x1][y1][x2][y2][num];

    if(num==0){
        double tmp = sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];
        return dp[x1][y1][x2][y2][num] = sqr(tmp-ave);
    }

    double tmp = INF;

    for(int i=x1+1;i<=x2;i++)
        rep(j,num)
            tmp = min(tmp,dfs(x1,y1,i-1,y2,j)+dfs(i,y1,x2,y2,num-j-1));

    for(int i=y1+1;i<=y2;i++)
        rep(j,num)
            tmp = min(tmp,dfs(x1,y1,x2,i-1,j)+dfs(x1,i,x2,y2,num-j-1));

    return dp[x1][y1][x2][y2][num] = tmp;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD3(n,m,d);
    rep1(i,n)
        rep1(j,m){
            scanf("%lf",&map[i][j]);
            ave += map[i][j];
            sum[i][j] = sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+map[i][j];
        }

    rep(i,N)
        rep(j,N)
            rep(x,N)
                rep(y,N)
                    rep(z,N)
                        dp[i][j][x][y][z] = INF;

    ave /= d;
    printf("%.2lf\n",sqrt(dfs(1,1,n,m,d-1)/d) );
	return 0;
}
