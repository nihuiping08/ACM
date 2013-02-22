/*
 * 题目：
 *		求出在n以内所有与n不互质的和
 *
 * 分析：
 *		我们可以先求出欧拉函数，算出n以内所有与n互质的数的个数，由于gcd(a,n)==1,所以
 *		gcd(n-a,n)==1，所以在n以内的所有与n互质的数是成对出现的。所以问题可以转化为
 *		ans = (n-1)*n/2-phi(n) * n /2;
 *
 * */
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

#define debug puts("here");

const int MOD = 1000000007;

ll euler(ll n){
	ll res = n;
	for(ll i=2;i*i<=n;i++)
		if(n%i==0){
			res = res/i*(i-1);
			while(n%i==0)
				n /= i;
		}
	if(n>1)
		res = res/n*(n-1);
	return res;
}

int main(){
	ll n;
	while(cin>>n,n)
		cout<<(n*(n-1)/2-n*euler(n)/2)%MOD<<endl;
    return 0;
}

