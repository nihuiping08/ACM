#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

	bool check(long long n){
		while(n!=1){
			if(!n||(n%5))
				return false;
			n /= 5;
		}
		return true;
	}
class
CuttingBitString
{
public:
	int getmin(string s){
		int n = s.size();
		const int X = 55;
		bool use[X][X];
		int a[55];
		for(int i=0;i<n;i++)
			a[i] = s[i]-'0';
		memset(use,0,sizeof(use));
		for(int i=0;i<n;i++){
			if(a[i]==0)
				continue;
			long long temp = 0;
			for(int j=i;j<n;j++){
				temp = (temp<<1)+a[j];
				if(temp&&(temp==1||check(temp))){
					use[i][j] = true;
					cout<<temp<<endl;
				}
			}
		}
		int dp[X];
		const int inf = 100000000;
		dp[0] = 0;
		for(int i=1;i<=n;i++){
			dp[i] = inf;
			for(int j=1;j<=i;j++){
				if(use[j-1][i-1]){
					dp[i] = min(dp[i],dp[j-1]+1);
				}
			}
		}
		if(dp[n]==inf)
			return -1;
		else
			return dp[n];
	}
};
