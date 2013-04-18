/*

題目：
    給出一個有向圖，現在依次刪除n個點，問每刪掉一個點時所有最短路的權和
分析：
    倒推，從刪除的第n個點出發，按照floyd的思想實現就行

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

const int MAXN = 505;
const int INF = 1e9;

int a[MAXN][MAXN],n;
int in[MAXN];
ll ans[MAXN];
bool use[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD(n)){

        rep1(i,n)
            rep1(j,n)
                RD(a[i][j]);
        rep1(i,n)
            RD(in[i]);

        memset(use,false,sizeof(use));
        memset(ans,0,sizeof(ans));

        for(int id=n;id;id--){
            int x = in[id];
            use[x] = true;
            rep1(i,n)
                rep1(j,n)
                    a[i][j] = min(a[i][j],a[i][x]+a[x][j]);

            rep1(i,n) if(use[i])
                rep1(j,n) if(use[j])
                    ans[id] += a[i][j];
        }

        rep1(i,n)
            cout<<ans[i]<<" ";
        cout<<endl;
    }

	return 0;
}
