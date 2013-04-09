/*

題目：
    有一个a*b的整数组成的矩阵，现请你从中找出一个n*n的正方形区域，
    使得该区域所有数中的最大值和最小值的差最小。
分析：
    二維單調隊列。
    1.先對行進行單調隊列的操作，記錄max[i][j],min[i][j]，表示從i-d+1到i行的最值。
    2.對於每列來說，我們同樣進行單調隊列操作，然後統計更新答案

*/
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

const int MAXN = 1005;
const int INF = 2e9;

int ax[MAXN][MAXN],bn[MAXN][MAXN];
int map[MAXN][MAXN],n,m,d;

struct node{
    int id,val;
}qmax[MAXN],qmin[MAXN];

void init(){ // 預處理，計算出max[i][j],min[i][j]
    rep1(j,m){
        int t1 = 0,t2 = 0,h1 = 0,h2 = 0;
        rep1(i,n){
            // 計算max的單調隊列
            while(h1<t1&&i-qmax[h1+1].id>=d) // 越界
                h1 ++;
            while(h1<t1&&qmax[t1].val<=map[i][j]) // 維護的是單調遞減的數列
                t1 --;
            qmax[++t1].val = map[i][j];
            qmax[t1].id = i;
            if(i<d)
                ax[i][j] = INF;
            else
                ax[i][j] = qmax[h1+1].val;

            // 計算min的單調隊列
            while(h2<t2&&i-qmin[h2+1].id>=d) // 越界
                h2 ++;
            while(h2<t2&&qmin[t2].val>=map[i][j]) // 維護的是單調遞增的數列
                t2 --;
            qmin[++t2].val = map[i][j];
            qmin[t2].id = i;
            if(i<d)
                bn[i][j] = 0;
            else
                bn[i][j] = qmin[h2+1].val;
        }
    }
}

void solve(){ // 在max以及min數組上面進行行的單調隊列操作。
    int ans = INF;
    for(int i=1;i<=n;i++){
        int h1 = 0,h2 = 0,t1 = 0,t2 = 0;
        for(int j=1;j<=m;j++){
            // 行的max
            while(h1<t1&&j-qmax[h1+1].id>=d)
                h1 ++;
            while(h1<t1&&qmax[t1].val<=ax[i][j])
                t1 --;
            qmax[++t1].val = ax[i][j];
            qmax[t1].id = j;

            // 行的min
            while(h2<t2&&j-qmin[h2+1].id>=d)
                h2 ++;
            while(h2<t2&&qmin[t2].val>=bn[i][j])
                t2 --;
            qmin[++t2].val = bn[i][j];
            qmin[t2].id = j;

            if(i>=d&&j>=d)
                ans = min(ans,qmax[h1+1].val-qmin[h2+1].val);
        }
    }
    cout<<ans<<endl;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD3(n,m,d)){
        rep1(i,n)
            rep1(j,m)
                RD(map[i][j]);
        init();
        solve();
    }

	return 0;
}
