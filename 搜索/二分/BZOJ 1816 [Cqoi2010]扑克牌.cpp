/*

題目：
    給出n張牌，數目分別爲ci。現在有一種特殊的牌joker，可以充當任意的
    牌。現在需要組成一副牌，即從1到n張牌都有，可以用joker充當，但是對於
    每副牌各種牌的數目最多為1。問可以組多少副牌。
分析：
    對於joker算為第0種牌，然後從n+1種牌當中選出n種牌，使得能夠選的數目
    最多。很顯然該問題與我們求的問題等價。
    對於該問題，我們可以通過二分來得到答案。

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

const int MAXN = 105;

ll a[MAXN],n;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n){
        n ++;
        rep1(i,n)
            cin>>a[i];
        sort(a+1,a+n+1);
        ll l = 0,r = 10000000000000000LL;
        ll ans = 0;
        while(l<=r){
            ll mid = (l+r)>>1;
            ll tmp = 0;
            rep1(i,n)
                if(a[i]<mid)
                    tmp += mid-a[i];
            if(tmp<=mid){
                ans = mid;
                l = mid+1;
            }else
                r = mid-1;
        }
        cout<<ans<<endl;
    }

	return 0;
}
