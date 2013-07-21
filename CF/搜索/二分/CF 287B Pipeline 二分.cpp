/*

题目:
    现在需要有n个插口，有插口为 2,3...k 共k-1个插排，现在问至少需要多少个插排
    使得插口数大于等于n个。刚开始的时候有一个插口

分析：
    二分，需要注意 n==1

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
#define Abs(x) max(x,-x)



int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    ll n,k;
    while(cin>>n>>k){
        if(n==1){
            puts("0");
            continue;
        }

        ll tmp = (k-1)*k/2;

        if(tmp+1<n){
            puts("-1");
            continue;
        }

        ll l = 1,r = k-1;
        ll ans = 0;
        while(l<=r){
            ll mid = (l+r)>>1;
            ll tmp = (mid+k-1)*(k-mid)/2+1;
            if(tmp>=n){
                ans = mid;
                l = mid+1;
            }else
                r = mid-1;
        }
        ans = k-ans;
        cout<<ans<<endl;
    }

	return 0;
}
