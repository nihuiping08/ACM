/*

题目:
    给出n个数，现在有m个区间询问l[i],r[i]，问如何重新排列这n个数，使得
    询问的和值最大

分析：
    方法一：差分数列
    一维的差分数列如下定义：
    假设原数组为a[1]...a[n],a[0] = 0
    差分数列数组为d[1]...d[n]
    则d[i] = a[i]-a[i-1] （d数组初始化）
    我们发现：a[i] = sigma(d[i])
    所以我们对于区间[l,r]执行加同一个数的时候，我们可以执行
    d[l] += val , d[r+1] -= val;
    最终，我们可以用差分数列的累加和计算a[i]的值。

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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)

string str;

const int X = 2e5+5;

int a[X],val[X];
int sum[X];

int main(){

#ifndef ONLINE_JUDGE
  freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,m;
    while(cin>>n>>m){
        rep(i,n)
            scanf("%d",&val[i+1]);
        int x,y;
        memset(a,0,sizeof(a));
        while(m--){
            scanf("%d%d",&x,&y);
            a[x] ++;
            a[y+1] --;
        }
        for(int i=1;i<=n;i++)
            sum[i] = sum[i-1]+a[i];
        sort(sum+1,sum+n+1);
        sort(val+1,val+n+1);
        ll ans = 0;
        REP(i,1,n+1)
            ans += (ll)val[i]*sum[i];
        cout<<ans<<endl;
    }

	return 0;
}

