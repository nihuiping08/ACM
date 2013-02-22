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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)

const int X = 55;

struct node{
  int x,y;
	node(){}
	node(int _x,int _y):x(_x),y(_y){}
};

vector<node> vec;
int kk,n,ans;
bool use[X];

class MagicMoleculeEasy{

public:

	int cal(int cnt,int sum,vector<int> val){
		vector<int> qq;
		for(int i=0;i<n;i++)
			if(!use[i])
				qq.pb(val[i]);
		sort(qq.begin(),qq.end());
		reverse( qq.begin() , qq.end() );
		int res = 0;
		for(int i=cnt;i<kk;i++)
			sum += qq[res++];
		return sum;
	}

	void dfs(int dep,int cnt,int sum,vector<int> val){
		if(cnt>kk)	return;
		if(dep==vec.size()){
			ans = max(ans,cal(cnt,sum,val));
			return;
		}
		
		int x = vec[dep].x;
		int y = vec[dep].y;
		if(	use[x] || use[y] ){
			dfs(dep+1,cnt,sum,val);
			return;
		}
		
		use[x] = 1;
		dfs(dep+1,cnt+1,sum+val[x],val);
		use[x] = 0;

		use[y] = 1;
		dfs(dep+1,cnt+1,sum+val[y],val);
		use[y] = 0;
	}

	int maxMagicPower(vector <int> val, vector <string> s, int k){
		n = val.size();
		kk = k;
		rep(i,n)
			for(int j=i;j<n;j++)
				if(s[i][j]=='Y')
					vec.pb(node(i,j));

		if(vec.size()==0){
			sort(val.begin() , val.end());
			reverse(val.begin(),val.end());
			int ans = 0;
			for(int i=0;i<k;i++)
				ans += val[i];
			return ans;
		}

		ans = -1;
		dfs(0,0,0,val);

		return ans;
	}
};
