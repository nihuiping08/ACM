/*

題目：
    給出原始數列a[1]...a[n]

    給出m個操作方式:
        l r val
    表示把a[l],...,a[r]都增加val

    現在需要執行以下op條操作:
        x y
    表示執行第x條操作方式到第y條操作方式

    詢問：最終的數列a

分析：
    一：線段樹
    顯然可以用線段樹成段更新。
    1.對於每個操作，我們可以用樹狀數組、線段樹、差分數列，統計一下每條操作方式的次數c[i]
    2.統計完之後對於每個操作方式進行成段更新，l_i r_i val_i*c[i]
    3.遞歸一次得到所有節點的值。

    二：樹狀數組
    樹狀數組，跟線段樹差不多。。。

    三：差分數列
    1.由於是每個操作都是成段進行對成段的更新。
    所以我們先對所有的操作用差分數列來統計一下每條操作方式執行的次數。

    2.統計出每條操作方式的次數后，對於每個操作方式進行又一次的差分操作。

    3.統計完之後直接加上原數列的大小即為答案


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

const int MAXN = 1e5+5;

int tmp[3][MAXN],a[MAXN];
ll ans[MAXN],t[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,m,op;
    while(~RD3(n,m,op)){
        rep1(i,n)
            RD(a[i]);

        memset(ans,0,sizeof(ans));
        memset(t,0,sizeof(t));

        rep1(i,m)
            RD3(tmp[0][i],tmp[1][i],tmp[2][i]);

        int x,y,z;
        while(op--){ /// 對於操作，統計出每條操作方式執行的次數
            RD2(x,y); // m
            ans[y+1] --;
            ans[x] ++;
        }
        rep1(i,m) /// 大小為m(我這裡WA了3次 = =。)
            ans[i] += ans[i-1];

        rep1(i,m){ /// 對於每條操作方式，進行又一次的差分操作
            x = tmp[0][i];
            y = tmp[1][i];
            z = tmp[2][i];
            ll qq = ll(z)*ans[i];
            t[y+1] -= qq;
            t[x] += qq;
        }
        rep1(i,n) /// 統計
            t[i] += t[i-1];

        rep1(i,n)
            cout<<t[i]+a[i]<<" ";
        cout<<endl;
    }

	return 0;
}
