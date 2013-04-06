/*

題目：
    n堆石子，每次可以從一堆中取任意石子，最後取石子的人為輸。問誰贏

分析：
    Nim遊戲的變形
    從后往前推：
    1:x     x>1贏，否則：
    2:1,x   x>1贏，否則：
    3:1,1,x x>1贏，否則：
    。。。
    所以我們可以推測，若全部都是1的話，則根據n的奇偶判斷
    否則，根據Nim遊戲判斷xor值

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

/******** program ********************/

const int MAXN = 55;

int a[MAXN],n;

bool ok(){
    if(a[0]==1)
        return !(n&1);
    int ans = 0;
    rep(i,n)
        ans = ans^a[i];
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    while(ncase--){
        RD(n);
        rep(i,n)
            RD(a[i]);
        sort(a,a+n);
        reverse(a,a+n);
        if(ok())
            puts("John");
        else
            puts("Brother");
    }

	return 0;
}
