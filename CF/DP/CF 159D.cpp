/*

在字符串s中寻找四元组a<=b<c<=d，使得[a,b],[c,d]分别为回文串	

dp[i][j] = dp[i+1][j-1]
表示以i开始，以j结束的串是一个回文串。则前后统计一下利用乘法原理计算即可。

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
#define fir first
#define sec second
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/

const int MAXN = 2005;

char s[MAXN];
bool is[MAXN][MAXN];
ll a[MAXN],b[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~scanf("%s",s+1)){
        memset(is,0,sizeof(is));
        int n = strlen(s+1);

        rep1(j,n)
            for(int i=j;i;i--)
                is[i][j] = (s[i]==s[j]) && ( j-i<=1 || is[i+1][j-1] );

        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));

        rep1(i,n)
            REP(j,1,i)
                a[i] += is[j][i];

        for(int i=n;i;i--){
            REP(j,i,n)
                b[i] += is[i][j];
            b[i] += b[i+1];
        }
        /*
        rep1(i,n)
            cout<<a[i]<<" ";
        cout<<endl;

        rep1(i,n)
            cout<<b[i]<<" ";
        cout<<endl;
        */

        ll ans = 0;
        rep1(i,n)
            ans += a[i]*b[i+1];
        cout<<ans<<endl;
    }

	return 0;
}
