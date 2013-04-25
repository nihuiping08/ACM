/*

題目：
    有n層蓄水層，每層現有wi的水，容量為li，破壞它需要pi費用。
    當一層被破壞之後或者水量超過容量的話，水自動流向下一層，
    問使得最後一層被破壞掉的最小費用
分析：
    最大堆。
    我們可以從後面開始枚舉該層被破壞，顯然時間複雜度為O(n^2)。
    所以我們可以用最大堆優化。
    每次插入的時候插入( sum[i]-limit[i],p[i] )
    然後每次如果sum[top]-limit[top]>sum[i-1]表示該位置的費用可以
    去掉，即只需把最高層的破壞掉之後會導致某些層自動破壞掉

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

const int MAXN = 15005;
const int INF = 1e9;

int w[MAXN],limit[MAXN],p[MAXN],sum[MAXN],n;

priority_queue< pair<int,int> > q;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD(n);
    rep1(i,n){
        RD3(w[i],limit[i],p[i]);
        sum[i] = sum[i-1]+w[i];
    }

    int best = 0 , ans = INF, total = 0;

    for(int i=n;i;i--){
        total += p[i];
        q.push( make_pair(sum[i]-limit[i],p[i]) );

        while( q.size() && q.top().first > sum[i-1] ){
            total -= q.top().second;
            q.pop();
        }

        if(total<ans){
            ans = total;
            best = i;
        }
    }

    REP(i,best,n)
        if(sum[i]-sum[best-1]<=limit[i])
            printf("%d\n",i);

	return 0;
}
