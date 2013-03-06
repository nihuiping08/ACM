/*

题目：
    给出数列a1...an，现在问[l,r]中，是否满足
    a[l]<=a[l+1]<=...<=a[k]>=a[k+1]....>=a[r]

分析：
    我们可以直接计算当前的数可以往后上升到的位置Inc，可以往前下降的位置
    Dec。然后判断Inc >= Dec是否满足就行了

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
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 1e5+5;

int a[MAXN],Dec[MAXN],Inc[MAXN];
int n,m;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD2(n,m);
    rep(i,n)
        RD(a[i]);

    Inc[n-1] = n;
    for(int i=n-2;i>=0;i--){
        if(a[i]<=a[i+1])
            Inc[i] = Inc[i+1];
        else
            Inc[i] = i;
    }

    REP(i,1,n){
        if(a[i]<=a[i-1])
            Dec[i] = Dec[i-1];
        else
            Dec[i] = i;
    }

    int x,y;
    while(m--){
        RD2(x,y);
        if(Dec[--y]<=Inc[--x])
            puts("Yes");
        else
            puts("No");
    }

	return 0;
}
