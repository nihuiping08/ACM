#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

#define debug puts("here")

LL pw(LL a,LL b,LL mod){
	LL res = 1;
	while(b>0){
		if(b&1)
			res = res*a%mod;
		a = a*a%mod;
		b >>= 1;
	}
	return res;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("suma.txt","r",stdin);
#endif

	int ncase;
	cin>>ncase;
	while(ncase--){
		LL n,mod;
		scanf("%lld%lld",&mod,&n);
		LL ans = 0,a,b;
		while(n--){
			cin>>a>>b;
			ans = (ans+pw(a,b,mod))%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}