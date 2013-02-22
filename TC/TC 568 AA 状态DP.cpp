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

class 
BallsSeparating{
public :
	int c(int x){
		return x?1:0;
	}
	int minOperations(vector <int> a, vector <int> b, vector <int> c){
		int n = a.size();
		int dp[51][10];
		memset(dp,0x3f,sizeof(dp));
		dp[0][0] = 0;
		rep(i,n){
			rep(j,8){
				dp[i+1][ j | 1 ] = min(dp[i+1][ j | 1] , dp[i][j]+b[i]+c[i]);
				dp[i+1][ j | 2 ] = min(dp[i+1][ j | 2] , dp[i][j]+a[i]+c[i]);
				dp[i+1][ j | 4 ] = min(dp[i+1][ j | 4] , dp[i][j]+a[i]+b[i]);
			}
		}
		return dp[n][7]==dp[n][8]?-1:dp[n][7];
	}
};