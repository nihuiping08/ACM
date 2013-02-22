/*
 * ��Ŀ��
 *		( 1^b + 2^b + ... + a^b ) % a
 * ������
 *		a | [ i^b + (a-i)^b ]�����Կ���ֱ�ӿ����� 
 *
 * */
#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;

ll cal(ll a,ll b,ll mod){
	ll res = 1;
	while(b>0){
		if(b&1)
			res = res*a%mod;
		a = a*a%mod;
		b >>= 1;
	}
	return res;
}

int main(){
	ll a,b;
	while(cin>>a>>b){
		if(a&1)
			puts("0");
		else
			cout<<cal(a/2,b,a)<<endl;
	}
	return 0;
}
