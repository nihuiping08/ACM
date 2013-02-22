#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

bool check(vector <int> a,int ans){
	int len = a.size();
	a[0] = max(1,a[0]-ans);
	for(int i=1;i<len;i++){
		if(a[i]>a[i-1])
			a[i] = max(a[i]-ans,a[i-1]+1);
		else{
			if(a[i]+ans<=a[i-1])
				return false;
			a[i] = min(a[i]+ans,a[i-1]+1);
		}
	}
	return true;
}

int binary(vector <int> a){
	int l = 1,r = 1000000000;
	int mid;
	while(l<r){
		mid = (r+l)>>1;
		if(check(a,mid))
			r = mid-1;
		else
			l = mid+1;
	}
	if(check(a,l)){
		if(check(a,l-1))
			return l-1;
		else
			return l;
	}
	else
		return l+1;
}

class  KingdomAndTrees{
public:
	int minLevel(vector <int> a){
		return binary(a);
	}
};