/*
 * 题目：
 *		找出第k个与n互质的数
 *
 *	分析：
 *		我们可以二分答案ans，然后在1-ans之间有多少个与n互质的数，可以用容斥原理来求
 *
 * */
#include <cstdio>
#include <iostream>

using namespace std;

typedef __int64 ll;

#define debug puts("here")

int di[10];
int cntd;

void fun(int n){
	cntd = 0;
	for(int i=2;i*i<=n;i++)
		if(n%i==0){
			di[cntd++] = i;
			while(n%i==0)
				n /= i;
		}
	if(n>1)
		di[cntd++] = n;
}

ll cal(ll n){
	ll sum = 0;
	for(int i=1;i<(1<<cntd);i++){
		ll s = 1;
		bool ok = false;
		for(int j=0;j<cntd;j++)
			if(i & (1<<j)){
				s *= di[j];
				ok = !ok;
			}
		if(ok)
			sum += n/s;
		else
			sum -= n/s;
	}
	return n-sum;
}

void solve(int n,int k){
	fun(n);
	ll l = 0,r = (ll)1<<62;
	ll ans = 0;
	while(l<=r){
		ll mid = (l+r)>>1;
		ll temp = cal(mid);
		if(temp>=k){
			if(temp==k)
				ans = mid;
			r = mid-1;
		}
		else
			l = mid+1;
	}
	cout<<ans<<endl;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("sum_a.in","r",stdin);
#endif

	int n,k;
	while(~scanf("%d%d",&n,&k))
		solve(n,k);
	return 0;
}
