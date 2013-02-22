/*
 * 题目：
 *		求0<a<b<=n中，所有的最简分数a/b的个数
 *
 * 分析：
 *		直接可以化成求sigma( phi(n) )。然后转化为快速求欧拉函数。
 *		
 *		m的既约剩余系的个数称为记为φ(m).通常称为欧拉函数。
 *		显然，φ(m) 等于1->m中与m互质的数的个数。
 *		
 *
 * */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

using namespace std;

const int X = 1000005;

typedef long long ll;

ll ans[X];
bool use[X];

void init(){
	memset(use,false,sizeof(use));
	for(int i=1;i<X;i++)
		ans[i] = i;
	for(int i=2;i<X;i++)
		if(!use[i]){
			for(int j=i;j<X;j+=i){
				use[j] = true;
				ans[j] = ans[j]/i*(i-1);
			}
		}
	ans[2] = 1;
	for(int i=3;i<X;i++)
		ans[i] += ans[i-1];
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("sum.txt","r",stdin);
#endif
	int n;
	init();
	while(scanf("%d",&n),n)
		printf("%lld\n",ans[n]);

	return 0;
}

