/*

题目：
    给出一幅二维格子地图，然后每次会有三种去向（消耗均为2），概率分别为
    pr(向右),pd(向下),p(原地)，现在某人从格子[1,1]出发，问到达[n,m]的期望消耗
    是多少

分析：
    根据期望公式，不难想到期望公式如下: dp[i][j]表示从[i,j]出发到达[n,m]的期望
    消耗。
    dp[i][j] = (dp[i][j]+2)*p[i][j]+(dp[i+1][j]+2)*pd[i][j]+(dp[i][j+1]+2)*pr[i][j];
    由于等式右面有dp[i][j]，移项后即可解出答案dp[1][1]
    注意当a[i][j] == 1时，该格子不能再往下走，所以得要特殊处理。。。

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int X = 1005;

double PD[X][X],PR[X][X],P[X][X];
double dp[X][X];
int n,m;

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%lf%lf%lf",&P[i][j],&PR[i][j],&PD[i][j]);
        memset(dp,0,sizeof(dp));
        for(int i=n;i;i--)
            for(int j=m;j;j--){
                double temp = 0;
                if(P[i][j]<1){
                    temp = (2+dp[i+1][j])*PD[i][j]+(2+dp[i][j+1])*PR[i][j]+2*P[i][j];
                    temp /= 1-P[i][j];
                }
                dp[i][j] = temp;
            }
        printf("%.3lf\n",dp[1][1]);
    }
    return 0;
}
