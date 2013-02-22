/*

题目：
    问一个数n最少是多少个完全平方数的和

分析：
    简单的01背包问题，dp[i] = min(dp[i-a[j]]+1]);

*/
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int maxm = 60100;
const int maxn = 245;
const int inf = 1e9;

int n,dp[maxm];
int a[maxn];

void init(){
    for(int i=0;i<maxm;i++)
        dp[i] = inf;
    dp[0] = 0;

    for(int i=0;i<maxn;i++)
        a[i] = i*i;

    for(int i=1;i<maxm;i++)
        for(int j=1;a[j]<=i;j++)
            dp[i] = min(dp[i],dp[i-a[j]]+1);
}

int main(){
    freopen("sum.in","r",stdin);
    init();
    while(cin>>n){
        cout<<dp[n]<<endl;
    }
    return 0;
}
