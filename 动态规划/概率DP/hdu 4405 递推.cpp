/*

题目：飞行棋，每一次跳跃仍sai子决定。有m个跳跃点，从跳跃点x可以跳到y，并且可以连续跳跃，问
	从0跳到位置n的跳跃期望次数
	
分析：
	期望一般从后往前递推
	当可以跳跃时，期望其实跟跳跃之后的概率是一样的。
	否则：
	dp[i] = sgima(dp[ i+j ]/6)+1

*/
#include <set>
#include <map>
#include <list>
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
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)
#define All(vec) vec.begin(),vec.end()
#define MP make_pair
#define PII pair<int,int>
#define PQ priority_queue
#define cmax(x,y) x = max(x,y)
#define cmin(x,y) x = min(x,y)
#define Clear(x) memset(x,0,sizeof(x))
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/

const int MAXN = 100005;

int to[MAXN];
double dp[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,m,x,y;
    while(cin>>n>>m,n||m){
        Clear(to);
        while(m--){
            RD2(x,y);
            to[x] = y;
        }

        double per = 1.0/6;
        Clear(dp);
        dp[n] = 0;
        for(int i=n-1;i>=0;i--){
            if(to[i]){
                dp[i] = dp[to[i]];
                continue;
            }
            rep1(j,6)
                dp[i] += per*dp[ i+j ];
            dp[i] ++;
        }
        printf("%.4lf\n",dp[0]);
    }

	return 0;
}
