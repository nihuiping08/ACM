/*

題目：給出一棵樹，尋找樹上的三個點a,b,c，使得ab+bc的和最大(bc<ac)
分析：我們可以證明ac為樹上的直徑。所以我們可以先dfs兩次求出樹上的直徑，
然後再通過枚舉中間的b節點即為答案

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

const int MAXN = 200005;

int po[MAXN],tol,n,m;
ll val[MAXN],now,ans;
int dot;

struct node{
    int y,val,next;
}edge[MAXN<<1];

void add(int x,int y,int v){
    edge[++tol].y = y;
    edge[tol].val = v;
    edge[tol].next = po[x];
    po[x] = tol;
}

void dfs_len(int x,int fa,ll tot){
    if(tot>now){
        now = tot;
        dot = x;
    }
    val[x] = min(val[x],tot);
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)   continue;
        dfs_len(y,x,edge[i].val+tot);
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD2(n,m)){
        int x,y,z;
        memset(po,0,sizeof(po));
        tol = 0;
        while(m--){
            RD3(x,y,z);
            add(x,y,z);
            add(y,x,z);
        }

        now = 0;
        dfs_len(1,0,0);
        int a = dot;

        memset(val,0x7f,sizeof(val));

        now = 0;
        dfs_len(a,0,0);
        int b = dot;
        now = 0;
        dfs_len(b,0,0);

        ans = 0;
        rep1(i,n)
            if(i!=a&&i!=b)
                ans = max(ans,val[i]+now);

        cout<<ans<<endl;
    }

	return 0;
}
