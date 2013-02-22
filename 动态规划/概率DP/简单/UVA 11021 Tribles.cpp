/*

题目：
    第一天的时候，有k个小鸟（Trible），她只能活一天，在她死之前，生下i个小鸟的
    概率为p[i]，问第m天（包括m天之前）全死亡的概率。（小鸟最多能够生下n-1个后代）

分析：
    独立概率问题，由于k只小鸟相互独立，所以求出一只小鸟以及她的后代在m天之内全
    死亡的概率dp[m]，答案就为dp[m]^k。
    考虑：
    m = 1，概率为p[0]，即没有生下后代
    m = i，若第一天小鸟生下了i个后代的时候，即这i个小鸟得要在第i天都得死，这
    i个小鸟以及她们的后代只能够存活i-1天，有全概率公式，
    dp[i] = p[0]+p[1]*f[i-1]+p[2]*f[i-1]^2+...+p[n-1]*f[i-1]^(n-1)

    考虑p[j]*f[i-1]^j，表示第一天的小鸟生下了j个后代，要在i天全死，所以这j个
    后代又分别考虑，把第二天看成这j个小鸟的第一天，相当于子问题，然后得要在
    i-1天死亡，且j个小鸟相互独立，所以递推公式很容易想到了

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int X = 1005;

double p[X],dp[X];
int n,k,m;

int main(){
    freopen("sum.in","r",stdin);
    int ncase,cnt = 0;
    cin>>ncase;
    while(ncase--){
        cin>>n>>k>>m;
        for(int i=0;i<n;i++)
            cin>>p[i];
        dp[0] = 0;
        dp[1] = p[0];
        for(int i=2;i<=m;i++){
            dp[i] = p[0];
            for(int j=1;j<n;j++)
                dp[i] += p[j]*pow(dp[i-1],j);
        }
        dp[m] = pow(dp[m],k);
        printf("Case #%d: %.7lf\n",++cnt,dp[m]);
    }
    return 0;
}
