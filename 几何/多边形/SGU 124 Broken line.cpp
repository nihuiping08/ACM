/*

題目：給出一個多邊形，問點與多邊形的位置關係
分析：作豎直向下的直線與多邊形的相交次數來判斷。但是可能會出現
    該直線與多邊形一條邊相交的情況。由於都是整點，所以我們可以
    先判斷是否在邊界上面，不在的話，再把原來的多邊形的說有點擴大
    一倍之後，把判斷的點擴大一倍減一，表示移動一個極小量，但是
    顯然這時不會影響位置關係。

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

const int MAXN = 1e4+5;

int n,sx,sy;

struct node{
    int x,y;
    void rd(){
        RD2(x,y);
    }
    void db(){
        x <<= 1;
        y <<= 1;
    }
};
struct Point{
    node a,b;
    void rd(){
        a.rd();
        b.rd();
        if(a.x>b.x)swap(a.x,b.x);
        if(a.y>b.y)swap(a.y,b.y);
    }
    void db(){
        a.db();
        b.db();
    }
}p[MAXN];

bool BORDER(){ // 先判斷是否在邊界上
    rep1(i,n){
        if( p[i].a.x==p[i].b.x && p[i].a.x==sx && p[i].a.y<=sy&&sy<=p[i].b.y )
            return true;
        if( p[i].a.y==p[i].b.y && p[i].a.y==sy && p[i].a.x<=sx&&sx<=p[i].b.x )
            return true;
    }
    return false;
}

void solve(){
    // 移動一點距離不會影響是否在多邊形內部
    rep1(i,n)
        p[i].db();
    sx = sx*2-1;
    sy = sy*2-1;

    int ans = 0;
    rep1(i,n){
        if( sy>p[i].a.y&&p[i].a.y==p[i].b.y&&sx>=p[i].a.x&&sx<=p[i].b.x )
            ans ++;
    }
    if(ans&1)
        puts("INSIDE");
    else
        puts("OUTSIDE");
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD(n)){
        rep1(i,n)
            p[i].rd();
        RD2(sx,sy);
        if(BORDER())
            puts("BORDER");
        else
            solve();
    }

	return 0;
}
