/*

題目：給出一棵帶有邊權的樹，問所有節點能夠到達的最遠距離
分析：樹形DP
    先用dfs求出從每個節點能夠到達的最遠以及次最遠距離，記為fir[x],sec[x]
    然後第二次dfs時，每個節點的最遠距離為
    max( fir[x] , max_fa+edge_fa_x )
    max_fa表示父節點能夠去的最遠距離
    edge_fa_x表示邊fa_x的邊權

    max_fa為 max{ fir[fa] || sec[fa](當x在fir的路徑上時) , max_fa_fa }

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

const int MAXN = 10005;

int po[MAXN],tol;
int fir[MAXN],sec[MAXN],dp[MAXN];
int now,ans,n;

struct node{
    int y,val,next;
}edge[MAXN<<1];

void add(int x,int y,int val){
    edge[++tol].y = y;
    edge[tol].val = val;
    edge[tol].next = po[x];
    po[x] = tol;
}

void dfs_1(int x,int fa){
    fir[x] = sec[x] = 0;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)   continue;
        dfs_1(y,x);
        int tmp = fir[y]+edge[i].val;
        if(fir[x]<=tmp){ /// 可能最長跟次長一樣
            sec[x] = fir[x];
            fir[x] = tmp;
        }else if(sec[x]<tmp)
            sec[x] = tmp;
    }
}

void dfs_2(int x,int fa,int tot){
    //cout<<x<<" "<<tot<<" "<<fir[x]<<" "<<sec[x]<<endl;
    dp[x] = max(tot,fir[x]);

    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)
            continue;
        int tmp = tot;
        if(fir[x]==fir[y]+edge[i].val)
            tmp = max(tmp,sec[x]);
        else
            tmp = max(tmp,fir[x]);
        dfs_2(y,x,tmp+edge[i].val);
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD(n)){
        memset(po,0,sizeof(po));
        tol = 0;
        int y,val;
        REP(x,2,n){
            RD2(y,val);
            add(x,y,val);
            add(y,x,val);
        }
        //memset(dp,0,sizeof(dp));
        dfs_1(1,0);
        dfs_2(1,0,0);
        rep1(i,n)
            printf("%d\n", dp[i] );
    }

	return 0;
}
