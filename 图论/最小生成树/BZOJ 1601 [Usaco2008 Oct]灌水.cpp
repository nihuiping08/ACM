/*

题目：
    裸的最小生成树

*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)

const int MAXN = 305;

int map[MAXN][MAXN],dis[MAXN];
bool use[MAXN];
int n,m;

void prim(){
    memset(use,0,sizeof(use));
    memset(dis,0x3f,sizeof(dis));

    dis[1] = 0;
    int ans = 0;
    int k;
    for(int i=0;i<n;i++){
        int MIN = dis[0];

        for(int j=1;j<=n;j++)
            if(!use[j]&&dis[j]<MIN)
                MIN = dis[ k = j ];

        use[k] = true;
        ans += MIN;
        for(int j=1;j<=n;j++)
            if(!use[j])
                dis[j] = min(dis[j],map[k][j]);
    }
    cout<<ans<<endl;
}

int main(){

#ifndef ONLINE_JUDGE
  freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD(n);
    for(int i=1;i<=n;i++){
        RD(map[i][n+1]);
        map[n+1][i] = map[i][n+1];
    }

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            RD(map[i][j]);

    n ++;
    prim();

	return 0;
}

