/*

题目：
    给出一个二进制的字符串，问它能够用最短的2^a1 + 2^a2...-2^b1...
    来表示。
    比如
    1101101 = 2^7-2^4-2^2+2^0，答案为4

分析：
    对于两个或者两个以上的1贪心就能够过了。

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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 1e6+5;

char s[MAXN];
int n;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>s){
        int n = strlen(s);
        reverse(s,s+n);

        for(int i=0;i<n;){
            if( s[i]=='1' ){
                int j = i;
                while(j<n && s[j]=='1')
                    j ++;
                if(j-i>=2){
                    s[i] = '1';
                    for(int k=i+1;k<j;k++)
                        s[k] = '0';
                    s[j] = '1';
                }
                i = j;
            }else
                i ++;
        }

        int ans = 0;
        for(int i=0;i<n+2;i++)
            ans += s[i]=='1';
        cout<<ans<<endl;
    }

	return 0;
}
