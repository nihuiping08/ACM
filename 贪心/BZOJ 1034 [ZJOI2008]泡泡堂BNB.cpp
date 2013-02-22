/*
 *	分析：
 *		贪心：
 *			1.当自己最小的能够战胜对方最小的，+2
 *			2.当自己最大的能够战胜对方最大的，+2
 *			3.用自己最小的跟对方最大的比较，+1 or +0
 *
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int X = 100005;

int n;

int solve(int a[],int b[]){
	int ans = 0;
	int la = 0,ra = n-1;
	int lb = 0,rb = n-1;
	for(int i=0;i<n;i++){
		if(a[la]>b[lb]){
			ans += 2;
			la ++;
			lb ++;
			continue;
		}
		if(a[ra]>b[rb]){
			ans += 2;
			ra --;
			rb --;
			continue;
		}
		if(a[la]==b[rb]){
			ans ++;
			la ++;
			rb --;
		}
		else{
			la ++;
			rb --;
		}
	}
	return ans;
}

int a[X],b[X];

int main(){
	while(cin>>n){
		for(int i=0;i<n;i++)
			scanf("%d",a+i);
		for(int i=0;i<n;i++)
			scanf("%d",b+i);
		sort(a,a+n);
		sort(b,b+n);
		cout<<solve(a,b)<<" "<<2*n-solve(b,a)<<endl;
	}
	return 0;
}
