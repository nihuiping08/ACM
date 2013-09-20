/*

题目：

　　给出一个字符串（均有小写字母组成），如果有长度为100的回文子串，输出该子串。否则输出
	最长的回文子串。

分析：

　　虽然输入串的长度比较长，但是如果存在单个字母100或以上的话，直接输出即可。

　　利用抽屉原理发现，如果不存在上面所说的情况，长度不会超过26*99

　　dp[l][r]表示l到r的回文子串的长度，dp转移方式比较明显，记录一下得到最优值时的位置。

　　输出方案时，如果dp[1][len]>=100的话，显然可以输出长度100的子串，否则直接输出该长度。

　　具体实现用到了栈、队列保存信息，可以看代码。

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
/*

#pragma comment(linker, "/STACK:1024000000,1024000000")

int size = 256 << 20; // 256MB
char *p = (char*)malloc(size) + size;
__asm__("movl %0, %%esp\n" :: "r"(p) );

*/

char IN;
bool NEG;
inline void Int(int &x){
    NEG = 0;
    while(!isdigit(IN=getchar()))
        if(IN=='-')NEG = 1;
    x = IN-'0';
    while(isdigit(IN=getchar()))
        x = x*10+IN-'0';
    if(NEG)x = -x;
}
inline void LL(ll &x){
    NEG = 0;
    while(!isdigit(IN=getchar()))
        if(IN=='-')NEG = 1;
    x = IN-'0';
    while(isdigit(IN=getchar()))
        x = x*10+IN-'0';
    if(NEG)x = -x;
}

/******** program ********************/

const int MAXN = 3005;

int cnt[MAXN];
int dp[MAXN][MAXN];
int px[MAXN][MAXN],py[MAXN][MAXN];
int n;
string s,a;
stack<char> b;

inline bool check(){
    rep(i,26)
        if(cnt[i]>=100){
            rep(j,100)
                putchar( char(i+'a') );
            puts("");
            return true;
        }
    return false;
}

int dfs(int l,int r){
    if(l==r)return dp[l][r] = 1;
    if(l>r) return dp[l][r] = 0;
    if(~dp[l][r])return dp[l][r];

    dp[l][r] = 0;
    if(s[l]==s[r]){
        px[l][r] = l+1;
        py[l][r] = r-1;
        dp[l][r] = dfs(l+1,r-1)+2;
    }
    int t = dfs(l+1,r);
    if(t>dp[l][r]){
        dp[l][r] = t;
        px[l][r] = l+1;
        py[l][r] = r;
    }

    t = dfs(l,r-1);
    if(t>dp[l][r]){
        dp[l][r] = t;
        px[l][r] = l;
        py[l][r] = r-1;
    }
    return dp[l][r];
}

void path(int l,int r,int res){ // 区间l,r输出长度res的回文子串
    int x = px[l][r] , y = py[l][r];
    if(l==x&&y==r){
        if(res){ // 如果还有
            a.pb(s[x]);
            res --;
        }
        return;
    }
    if(dp[l][r]==2+dp[x][y]){
        if(res){ // 如果还可以输出
            a.pb(s[l]);
            b.push(s[r]);
            res -= 2;
        }
    }
    path(x,y,res);
}

inline void print(){ // 输出方案
    foreach(i,a)
        putchar(a[i]);
    while(!b.empty()){
        putchar( b.top() );
        b.pop();
    }
    puts("");
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    while(getline(cin,s)){
        Clear(cnt);
        foreach(i,s)
            cnt[ s[i]-'a' ] ++;
        if(check())continue;
        n = s.size();
        rep(i,n)
            rep(j,n)
                px[i][j] = i , py[i][j] = j;

        memset(dp,-1,sizeof(dp));
        int len = dfs(0,s.size()-1);

        a.clear();
        path( 0,s.size()-1,min(100,len) );
        print();
    }

    return 0;
}
