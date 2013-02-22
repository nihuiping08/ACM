/*

题目：
    有m道题目，t支队伍，要求每支队伍至少A一道题，并且冠军队伍至少对n道题目，
    现在问这个要求的概率。

分析:
    dp[k][i][j]表示第k支队伍，在做完了前i道题目的情况下，对了j道题的概率，不难
    想出：dp[k][i][j] = dp[k][i-1][j]*(1-p[k][i])+dp[k][i-1][j-1]*p[k][i]。
    p[k][i]表示第k支队伍过i题的概率
    然后，由于题目要求的是每支队伍至少A一题，并且冠军队伍至少对n道题，所以可以
    用所有队伍均至少过了一题的概率减掉所有队伍至多对了不超过n道（不包括）的概率
    即可

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int M = 1001;
const int N = 31;

double dp[M][N][N],a,b;
double p[N],qq[M][N];
int n,m,t;

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>m>>t>>n,m||t||n)
    {
        for(int k=1;k<=t;k++)
        {
            for(int j=1;j<=m;j++)
                scanf("%lf",&p[j]);
            for(int i=0;i<=m;i++)
                for(int j=0;j<=m;j++)
                    dp[k][i][j] = 0.000;
            dp[k][0][0] = 1.000;
            for(int i=1;i<=m;i++)
                for(int j=0;j<=i;j++)
                {
                    if(j==0)
                        dp[k][i][0] = dp[k][i-1][0]*(1.000-p[i]);
                    else
                        dp[k][i][j] = dp[k][i-1][j-1]*p[i]+dp[k][i-1][j]*(1.000-p[i]);
                }
        }
        a = b = 1.000;
        for(int k=1;k<=t;k++)
        {
            a *= (1.000-dp[k][m][0]);
            double temp = 0.0;
            for(int j=1;j<n;j++)
                temp += dp[k][m][j];
            b *= temp;
        }
        printf("%.3lf\n",a-b);
    }
    return 0;
}
