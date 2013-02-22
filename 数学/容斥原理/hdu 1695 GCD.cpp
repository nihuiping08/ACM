/*
 * 见题解
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

typedef __int64 ll;

const int X = 100002;

int prime[X][8],top[X];
ll eular[X];

void init(){
	memset(top,0,sizeof(top));
	memset(eular,0,sizeof(eular));
	eular[1] = 1;
	for(int i=2;i<X;i++){
		if(!eular[i]){
			for(int j=i;j<X;j+=i){
				if(!eular[j])
					eular[j] = j;
				eular[j] = eular[j] / i * (i-1);
				prime[j][top[j]++] = i;
			}
		}
		eular[i] += eular[i-1];
	}
}

ll dfs(int x,int b,int now){ // 求不大于b的数中与now不互质的个数 , 容斥原理
	ll ans = 0;
	for(int i=x;i<top[now];i++){
		int temp = b/prime[now][i];
		ans += temp - dfs(i+1,temp,now);
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("sum_a.in","r",stdin);
#endif
	
	int ncase;
	cin >> ncase;
	int qq = 0;
	init();
	while(ncase--){
		printf("Case %d: ",++qq);
		int a,b,c,d,k;
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		if(!k){
			puts("0");
			continue;
		}
		if(b>d)
			swap(b,d);
		b /= k;
		d /= k;
		ll ans = eular[b];
		for(int i=b+1;i<=d;i++)
			ans += b-dfs(0,b,i);
		cout<<ans<<endl;
	}
	return 0;
}

