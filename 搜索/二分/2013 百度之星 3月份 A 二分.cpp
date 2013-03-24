/*

題目：
    給出n個數，把他們劃分為m個集合，問最小化最大的集合和值

分析：
    二分

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
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

const int MAXN = 1e4+5;

int a[MAXN],n,m;

bool solve(int mid){
    int ans = 0,sum = 0;
    rep1(i,n){
        if(a[i]>mid)
            return false;
        if(sum+a[i]<=mid)
            sum += a[i];
        else{
            sum = a[i];
            ans ++;
        }
    }
    return ans<m;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(RD2(n,m),n||m){
        int l = 0,r = 0;
        rep1(i,n){
            RD(a[i]);
            l = max(a[i],l);
            r += a[i];
        }
        int ans = 0;
        while(l<=r){
            int mid =  (l+r)>>1;
            if(solve(mid)){
                ans = mid;
                r = mid-1;
            }else
                l = mid+1;
        }
        cout<<ans<<endl;
    }

	return 0;
}
