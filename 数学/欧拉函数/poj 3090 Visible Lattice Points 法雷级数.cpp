/*
 * 题目：
 *		裸的欧拉函数
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

const int X = 1005;

int euler[X];

void init(){
	memset(euler,0,sizeof(euler));
	euler[1] = 1;
	for(int i=2;i<X;i++){
		if(!euler[i]){
			for(int j=i;j<X;j+=i){
				if(!euler[j])
					euler[j] = j;
				euler[j] = euler[j]/i*(i-1);
			}
		}
		euler[i] += euler[i-1];
	}
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("suma.in","r",stdin);
#endif
	init();
	int ncase,cnt = 0,n;
	cin>>ncase;
    while(ncase--){
		scanf("%d",&n);
		cout<<++cnt<<" "<<n<<" "<<euler[n]*2+1<<endl;
	}
	return 0;
}

