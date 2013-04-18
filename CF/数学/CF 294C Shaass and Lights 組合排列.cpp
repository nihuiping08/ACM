/*

題目：
    有n個燈，剛開始時有些燈是滅的，現在想要把所有的燈打開。如果某個燈
    是滅的並且他相鄰的燈至少有一個是開的才能夠打開。問打開燈的方案數
分析：
    排列組合。
    我們先統計每個連續滅的燈的長度為len_1...len_k
    對於每個連續的區間不按順序進行排列的方案數為
    sigma(len_i) ! / pi(len_i!)
    而對於每個區間來說，他的開燈方案數為2^(len_i-1)，即每個燈都可以從左
    或右打開。注意最後一個燈只有一種打開方式，所以是區間長度減1

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

const int MAXN = 1001;
const int MOD = 1e9+7;

ll comb[MAXN][MAXN],two[MAXN];
int a[MAXN],n,m;

void init(){
    rep(i,1001){
        comb[i][0] = 1;
        rep1(j,i)
            comb[i][j] = ( comb[i-1][j]+comb[i-1][j-1] )%MOD;
    }
    two[0] = 1;
    rep1(i,1000)
        two[i] = (two[i-1]<<1)%MOD;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    init();

    while(~RD2(n,m)){
        rep(i,m)
            RD(a[i]);
        sort(a,a+m);

        int all = n-m;
        ll ans = 1;
        ll sum = 1;

        if(a[0]-1)
            sum *= comb[all][a[0]-1];
        all -= a[0]-1;

        m --;
        rep1(i,m){
            if(a[i]-a[i-1]>=1){
                int x = a[i]-a[i-1]-1;
                sum = sum*comb[all][x]%MOD;
                ans = ans*two[x-1]%MOD;
                all -= x;
                //cout<<x<<" "<<all<<" "<<all+x<<" "<<sum<<endl;
            }
        }
        if(all)
            sum *= comb[all][all];
        sum %= MOD;
        //cout<<ans<<" "<<sum<<endl;
        ans = ans*sum%MOD;
        cout<<ans<<endl;
    }

	return 0;
}
