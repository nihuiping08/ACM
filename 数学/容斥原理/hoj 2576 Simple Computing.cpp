/*
 * 题目：
 *		给出一组数a1...an，问从1到m中能有多少个数能够最少能被这组数中的一个整除
 *
 *	分析：
 *		容斥原理，但是当3,6，m =18时，需要注意的是答案是6，所以需要求出的是这k个数的
 *		最小公倍数。详情看代码
 *
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define debug puts("here")

typedef long long ll;

const int X = 105;

int size;
int di[X];

int gcd(int x,int y){
	return x==0?y:gcd(y%x,x);
}

void cal(ll n){
	ll sum = 0;
	for(int i=1;i<(1<<size);i++){
		ll s = 1;
		bool ok = false;
		for(int j=0;j<size;j++)
			if( i & (1<<j) ){
				s = s/gcd(s,di[j])*di[j];
				ok = !ok;
			}
		if(ok)
			sum += n/s;
		else
			sum -= n/s;
	}
	cout<<sum<<endl;
}


int main(){
#ifndef ONLINE_JUDGE
	freopen("suma.txt","r",stdin);
#endif
	int ncase,m;
	cin>>ncase;
	while(ncase--){
		scanf("%d%d",&size,&m);
		for(int i=0;i<size;i++)
			scanf("%d",&di[i]);
		cal(m);
	}
	return 0;
}
