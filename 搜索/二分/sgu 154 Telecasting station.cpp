/*

题目：找出n!阶乘后面刚好有q个为0的最小的n
分析：二分n，然后再找n!末尾有多少个0。我们可以找n!有多少个5

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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

ll solve(ll n){
    ll ans = 0;
    while(n>=5){
        ans += n/5;
        n /= 5;
    }
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    ll n;
    cin>>n;
    if(n==0){
        puts("1");
        return 0;
    }
    ll l = 5,r = 1e12;
    ll ans = -1;
    while(l<=r){
        ll mid = (l+r)>>1;
        ll tmp = solve(mid);
        if(tmp==n){
            ans = mid;
            r = mid-1;
        }else if(tmp>n)
            r = mid-1;
        else
            l = mid+1;
    }
    if(ans==-1)
        puts("No solution");
    else
        cout<<ans<<endl;

	return 0;
}
