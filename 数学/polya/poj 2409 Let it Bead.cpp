/*
 * 题目：
 *		一个手镯，有n颗珠子，有t中颜色，对于珠子涂色，问去除等价之后珠子的涂色数目
 *
 *	分析：
 *		polya计数原理。
 *		对于手镯的涂色有两种情况：
 *		1.旋转：当然有n种旋转方式，分别为旋转i格，则循环节为gcd(i,n)。
 *		我们可以合情推理一下：
 *		1 2 3 4 5 6    1 2 3 4 5 6    1 2 3 4 5 6   1 2 3 4 5 6   1 2 3 4 5 6
 *		1 2 3 4 5 6    6 1 2 3 4 5    5 6 1 2 3 4   4 5 6 1 2 3   3 4 5 6 1 2
 *		
 *		1 2 3 4 5 6
 *		2 3 4 5 6 1
 *		我们可以对于每个群都可以分成gcd(i,n)个循环群。循环节为gcd(i,n)。
 *
 *		2.翻转：分两种情况讨论：
 *		 1）当n为奇数的时候，以每颗珠子作为旋转轴，对称轴有n条，而形成了长度为(n-1)/2
 *			 的循环，所以循环的个数为(n+1)
 *		 2）当n为偶数的时候，以每颗珠子作为旋转轴，对称轴有n/2条，而形成了n/2-1个长度为
 *			2的循环和两个长度为1的循环；以两颗珠子之间作为旋转轴，对称轴有n/2条，各形成
 *			n/2个长度为2的循环
 *
 * */
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

ll gcd(ll x,ll y){
	return x==0?y:gcd(y%x,x);
}

ll pw(ll x,ll sp){
	ll ans = 1;
	for(int i=0;i<sp;i++)
		ans *= x;
	return ans;
}

void polya(ll n,ll t){
	ll ans = 0;
	for(int i=1;i<=n;i++)
		ans += pw(t,gcd(i,n));
	if(n&1)
		ans += n*pw(t,(n+1)/2);
	else
		ans += n/2 * ( pw(t,n/2)+pw(t,n/2+1) );
	cout<<ans/(2*n)<<endl;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("sumd.txt","r",stdin);
#endif

	ll n,t;
	while(cin>>t>>n,t||n)
		polya(n,t);
	return 0;
}

