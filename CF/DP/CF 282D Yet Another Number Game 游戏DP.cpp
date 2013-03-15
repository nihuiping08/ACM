/*

题目：
    给出n个数，n<=3。现在有两个操作:
    1.选择ai，执行ai -= x,x<=ai
    2.选择一个x = min(ai) , i=1,...,n
    对于所有的ai执行ai -= x
    谁最后不能执行以上操作的就输了
    问输赢了

分析：
    1.若n=1，判断a1是否等于0
    2.若n=2，初始化为a[0][0] = 0，表示必输状态，然后向后可以执行的操作都算
    第一个人赢。
    3.若n=3，初始化为a[0][0][0] = 0，同上

*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int maxn = 301;

int dp[maxn][maxn];
int a[maxn][maxn][maxn];
int x,y,z,n;

bool f(){
    RD(n);

	if (n==1){
        RD(x);
		if(x)
			return true;
		else
			return false;
	}
	if (n==2){
	    RD2(x,y);
		dp[0][0] = 0;
		rep(i,x+1)
            rep(j,y+1)
				if (dp[i][j]==0){
					int tmp = min(x-i,y-j);
					rep1(d,tmp)
						dp[i+d][j+d] = 1;
                    rep1(d,x-i)
						dp[i+d][j] = 1;
                    rep1(d,y-j)
						dp[i][j+d] = 1;
				}
		return dp[x][y];
    }

    RD3(x,y,z);

	a[0][0][0] = 0;
	rep(i,x+1)
        rep(j,y+1)
			rep(k,z+1)
				if (a[i][j][k]==0){
					int tmp = min( x-i , min(y-j,z-k) );
                    rep1(d,tmp)
						a[i+d][j+d][k+d] = 1;
					rep1(d,x-i)
						a[i+d][j][k] = 1;
					rep1(d,y-j)
						a[i][j+d][k] = 1;
                    rep1(d,z-k)
						a[i][j][k+d] = 1;
				}
	return a[x][y][z];
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    if(f())
        puts("BitLGM");
    else
        puts("BitAryo");

	return 0;
}
