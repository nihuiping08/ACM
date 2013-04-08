/*

題目：
    給出序列，詢問m個長度為len_i的上升子序列，若有多個，需要輸出下標
    最小的那個。
分析：
    二分+LIS。首先二分求出LIS，用d[i]標記選了第i位置的最長公共子序列
    長度。
    然後對於每次詢問，暴力枚舉。。。

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

const int MAXN = 1e4+5;

int dp[MAXN],d[MAXN],a[MAXN],n,m;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD(n);
    rep1(i,n)
        RD(a[i]);

    int top = 0;

    for(int k=n;k;k--){
        int l = 1,r = top;
        while(l<=r){
            int mid = (l+r)>>1;
            if(dp[mid]>a[k])
                l = mid+1;
            else
                r = mid-1;
        }
        d[k] = l;
        dp[l] = a[k];
        top = max(top,l);
    }

    int x;
    RD(m);
    while(m--){
        RD(x);
        if(x>top){
            puts("Impossible");
            continue;
        }
        int pre = 0;
        for(int i=1;i<=n&&x;i++)
            if(d[i]>=x&&a[i]>pre){
                if(pre)
                    printf(" %d",a[i]);
                else
                    printf("%d",a[i]);
                pre = a[i];
                x --;
            }
        puts("");
    }

	return 0;
}
