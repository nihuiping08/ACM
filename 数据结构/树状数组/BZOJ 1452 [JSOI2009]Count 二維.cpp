/*

題目：
    給出一個n*m的矩陣，有兩種操作：
    1.更改x,y的顏色為c
    2.詢問x1,y1,x2,y2矩陣內顏色C的方格個數

分析：
    二維樹狀數組直接統計

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

int c[101][301][301];
int a[301][301];
int n,m;

int lowbit(int x){
    return x & -x;
}

void modify(int col,int x,int y,int val){
    int tmp = y;
    while(x<=n){
        y = tmp;
        while(y<=m){
            c[col][x][y] += val;
            y += lowbit(y);
        }
        x += lowbit(x);
    }
}

int ask(int col,int x,int y){
    int ans = 0;
    int tmp = y;
    while(x>0){
        y = tmp;
        while(y>0){
            ans += c[col][x][y];
            y -= lowbit(y);
        }
        x -= lowbit(x);
    }
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD2(n,m);
    rep1(i,n)
        rep1(j,m){
            RD(a[i][j]);
            modify(a[i][j],i,j,1);
        }

    int q,op,col,x,y,x2,y2;
    RD(q);
    while(q--){
        RD(op);
        if(op==1){
            RD3(x,y,col);
            modify(a[x][y],x,y,-1);
            modify( a[x][y]=col,x,y,1 );
        }else{
            RD4(x,x2,y,y2);
            RD(col);
            x --;
            y --;
            int ans = ask(col,x2,y2)+ask(col,x,y);
            ans -= (ask(col,x,y2)+ask(col,x2,y));
            printf("%d\n",ans);
        }
    }

	return 0;
}
