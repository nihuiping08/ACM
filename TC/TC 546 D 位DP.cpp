#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

#define debug puts("here");

class KleofasTail{
public:
	long long cal(long long a,long long b,long long cnt){
		if((a>>cnt)==(b>>cnt))
			return b-a+1;
		return 1LL<<cnt;
	}
	
	long long solve(long long a,long long b){
		if(a>b)
			return 0;
		if(a==0||b==0)
			return b-a+1;
		bool ok = a & 1;
		int cnt = 0;
		long long ans = 0;
		long long qq = a+1;
		while(1){
			if(!ok&&qq<=b)
				ans += cal(qq,b,cnt);
			if(a<=b)
				ans += cal(a,b,cnt);
			else break;
			a <<= 1;
			qq <<= 1;
			cnt++;
		}
		return ans;
	}
	
	long long countGoodSequences(long long K, long long A, long long B){
		cout<<K<<" "<<A<<" "<<B<<endl;
		cout<<solve(K,B)<<" "<<solve(K,A-1);
		return solve(K,B)-solve(K,A-1);
	}
};