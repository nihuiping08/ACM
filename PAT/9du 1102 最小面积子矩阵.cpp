/*

分析：
    用数组sum[i][j]维护从[1,1]到位置[i,j]的和值。
    然后直接枚举矩形的两个顶点（左上、右下），直接判断更新即可。

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
#define All(vec) vec.begin(),vec.end()
#define MP make_pair
#define PII pair<int,int>

/******** program ********************/

const int MAXN = 105;
const int INF = 1000000000;

int a[MAXN][MAXN],sum[MAXN][MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif


    int n,m,k;
    while(~RD3(n,m,k)){
        memset(sum,0,sizeof(sum));
        rep1(i,n)
            rep1(j,m){
                scanf("%d",&a[i][j]);
                sum[i][j] = sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
            }
        int ans = INF;

        rep1(i,n) // 枚举矩形的两个顶点[x,y]左上,[i,j]右下
        rep1(j,m)
        rep1(x,i)
        rep1(y,j)
        if(sum[i][j]-sum[i][y-1]-sum[x-1][j]+sum[x-1][y-1]>=k)
            ans = min(ans,(i-x+1)*(j-y+1));
        else // 小剪枝，可不写。
            break;

        if(ans!=INF)
            cout<<ans<<endl;
        else
            puts("-1");
    }
	return 0;
}
