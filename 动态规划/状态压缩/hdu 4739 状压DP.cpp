/*

题目：题目比较神，自己看题目吧

分析：

大概有两种思路：

1.dfs，枚举对角线，大概每次减少4个三角形，加上一些小剪枝的话可以过。

2.状压DP，先预处理出所有可以组成正方形的方案，根据题目的数据范围计算不会超过100个正方
形方案。n个正方形用二进制的方式记录，每一位记录是否还没引爆，则状态转移比较明显了。

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

PII p[22];
int px[22],py[22];
int a[100],n;
int dp[2][1<<21];

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    while(RD(n),~n){
        rep1(i,n)
            RD2(p[i].first,p[i].second);
        sort(p+1,p+n+1);
        rep1(i,n)
            px[i] = p[i].first , py[i] = p[i].second;

        int tp = 0;

        rep1(i,n) // 处理出所有可以组成的正方形
        REP(j,i+1,n)if(px[i]==px[j])
        REP(k,j+1,n)if(py[i]==py[k]||py[j]==py[k])
        REP(l,k+1,n)if(px[k]==px[l])
        if( (py[i]==py[k]&&py[j]==py[l])||(py[i]==py[l]&&py[j]==py[k]) )
        if( abs(px[i]-px[k])==abs(py[i]-py[j]) )
            a[++tp] = (1<<(i-1))|(1<<(j-1))|(1<<(k-1))|(1<<(l-1));

        Clear(dp);
        int all = 1<<n;
        int ans = 0;

        rep1(i,tp) // 状态压缩
            for(int sta=all-1;sta>=0;sta--){
                dp[i&1][sta] = dp[!(i&1)][sta];
                if( (a[i]&sta)!=a[i] )continue;
                cmax( dp[i&1][sta] , dp[!(i&1)][sta-a[i]]+4 );
                cmax(ans,dp[i&1][sta]);
            }
        cout<<ans<<endl;
    }

    return 0;
}
