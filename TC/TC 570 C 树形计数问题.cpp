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
typedef unsigned long long ull;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)

const int X = 55;

class 
CentaurCompanyDiv2{
public:

	vector<int> vec[X];
	int n;
	ll ans;
	
	ll dfs( int x,int pre){
		ll ret = 1;
		foreach(i,vec[x]){
			int y = vec[x][i];
			if(y==pre)	continue;
			ret *= (dfs(y,x)+1);
		}
		ans += ret;
		return ret;
	}
		
	long long count(vector <int> a, vector <int> b){
		n = a.size();
		rep(i,n){
			vec[ a[i] ].pb( b[i] );
			vec[ b[i] ].pb( a[i] );
		}
		ans = 0;
		dfs(1,-1);
		return ans+1;
	}
};