/*

题目：
    定义k回文串如下：
    1.任何串是一个0回文串
    2.一个长度为n的k回文串，当且仅当他的n/2的前缀和后缀都是k-1的回文串

分析：
    hash
    从左边开始，用le表示从左到目前位置的hash值，用ri表示从目前到第一位
    的hash值，如果两者相等，表示当前为回文串。再DP一下即可求出

*/
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
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

/******** program ********************/

const int MAXN = 5e6+5;
const int ha = 33;

ll dp[MAXN],le,ri;
string s;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(getline(cin,s)){
        dp[0] = 0;
        le = ri = 0;
        ll k = 1;
        memset(dp,0,sizeof(dp));
        ll ans = 0;
        foreach(i,s){
            le = le*ha + s[i]-'a';
            ri = ri+(s[i]-'a')*k;
            k *= ha;
            if(le==ri)
                dp[i+1] = dp[(i+1)/2]+1;
            ans += dp[i+1];
        }
        cout<<ans<<endl;
    }

    return 0;
}

