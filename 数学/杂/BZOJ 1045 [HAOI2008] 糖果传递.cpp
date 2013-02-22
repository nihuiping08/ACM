/*
 *	题目：
 *		有n个小朋友坐成一圈，每人有ai个糖果。每人只能给左右两人传递糖果。每人每次传
 *		递一个糖果代价为1，求使所有人获得均等糖果的最小代价。
 *
 *	分析：
 *		假设a1分给an的糖果数为k，则可以得到以下的信息：
 *			  a1		a2				a3		a4...		an-1  an
 *	当前数目：a1-k		a2				a3		a4			an-1  an+k
 *	所需代价：|a1-k-ave| |a1+a2-k-2*ave| |a1+a2+a3-k-3*ave|	|a1+..+a(n-1)-k-(n-1)*ave| |k|
 *	以sum[i]表示从a1加到ai减掉i*ave的和值，这以上可以化简为
 *	总代价 = |s1-k|+|s2-k|+...+|s(n-1)-k|+|k|
 *	不难看出：当k为s1...s(n-1)中的中位数的时候，所需的代价最小
 *
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int X = 1000005;

typedef long long ll;

ll sum[X],a[X];
ll n;

ll Abs(ll x){
	return max(x,-x);
}

int main(){
	freopen("sum.in","r",stdin);
	while(cin>>n){
		ll x;
		ll tot = 0;
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			tot += a[i];
		}
		
		ll ave = tot/n;
		for(int i=1;i<n;i++)
			sum[i] = a[i]+sum[i-1]-ave;
		sort(sum+1,sum+n);
		
		ll mid = sum[n/2];
		ll ans = Abs(mid);
		
		for(int i=1;i<n;i++)
			ans += Abs(sum[i]-mid);
		cout<<ans<<endl;
	}
	return 0;
}
