/*

題目：
    物流公司要把一批货物从码头A运到码头B。由于货物量比较大，需要n天才
    能运完。货物运输过程中一般要转停好几个码头。物流公司通常会设计一条
    固定的运输路线，以便对整个运输过程实施严格的管理和跟踪。由于各种因
    素的存在，有的时候某个码头会无法装卸货物。这时候就必须修改运输路
    线，让货物能够按时到达目的地。但是修改路线是一件十分麻烦的事情，会
    带来额外的成本。因此物流公司希望能够订一个n天的运输计划，使得总成
    本尽可能地小。

分析：
    最短路加dp：
    dp[i] = min( dp[j]+cost(j+1,i)+k ),i>j>=0
    dp[i]表示第i天的最優解
    cost(j,i)表示從第j天到第i天從源點到匯點的最短路，可以直接spfa求出

*/
#include <queue>
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

const int MAXN = 105;

int map[MAXN][MAXN],dis[MAXN],dp[MAXN],day,m,k,e;
int sum[MAXN][MAXN];
bool use[MAXN],ok[MAXN];

int spfa(int l,int r){
    memset(dis,0x3f,sizeof(dis));
    memset(use,false,sizeof(use));
    memset(ok,0,sizeof(ok));
    rep1(i,m)
        ok[i] = (sum[i][r]==sum[i][l]);
    dis[1] = 0;
    queue<int> q;
    q.push(1);
    while(q.size()){
        int x = q.front();
        q.pop();
        use[x] = false;
        rep1(y,m){
            if(map[x][y]&&ok[y]){
                int tmp = dis[x]+map[x][y];
                if(tmp<dis[y]){
                    dis[y] = tmp;
                    if(!use[y]){
                        use[y] = true;
                        q.push(y);
                    }
                }
            }
        }
    }
    return dis[m];
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD4(day,m,k,e);
    int x,y,z;
    while(e--){
        RD3(x,y,z);
        if(map[x][y]==0 || map[x][y]>z)
            map[x][y] = map[y][x] = z;
    }
    int bad;
    RD(bad);
    while(bad--){
        RD3(z,x,y);
        REP(i,x,y)
            sum[z][i] = 1;
    }
    rep1(i,m)
        rep1(j,day)
            sum[i][j] += sum[i][j-1];

    memset(dp,0x3f,sizeof(dp));
    dp[0] = 0;
    rep1(i,day)
        rep(j,i){
            int t = spfa(j,i);
            if(t==dis[0])
                continue;
            dp[i] = min(dp[i],dp[j]+t*(i-j)+k);
        }
    cout<<dp[day]-k<<endl;

	return 0;
}
