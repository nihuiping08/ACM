/*

题目:
    给出正整数n和k，计算j(n, k)=k mod 1 + k mod 2 + k mod 3 + … + k mod n的
    值，其中k mod i表示k除以i的余数

分析：
    分块计算。
    k%n = k-k/n，所以sum = n*m-sigma(k/i *i)
    k/i可以分成区间[ i,k/(k/i) )，在这个区间内的所有k/i值相等。所以可以划分为
    一个区间的等差数列来做

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

#define debug puts("here");

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    ll n,k;
    while(cin>>n>>k){
        ll ans = n*k;
        if(n>k)
            n = k;
        ll j = 0;
        for(ll i=1;i<=n;i=j+1){
            j = min(n,k/(k/i));
            ans -= (j-i+1)*(j+i)*(k/i)/2;
        }
        cout<<ans<<endl;
    }

	return 0;
}
