#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int X = 1005;

int s,n;
double dp[X][X];

int main()
{
    cin>>n>>s;
    dp[s][n] = dp[s+1][n] = dp[s][n+1] = 0;
    double temp = n*s*1.0;

    for(int i=n;i>=0;i--)
        for(int j=s;j>=0;j--)
        {
            if(i==n&&j==s)
                continue;
            dp[i][j] = temp;
            dp[i][j] += i*(s-j)*dp[i][j+1];
            dp[i][j] += (n-i)*(s-j)*dp[i+1][j+1];
            dp[i][j] += (n-i)*j*dp[i+1][j];
            dp[i][j] /= (temp-i*j);
            //printf("dp[%d][%d] = %lf\n",i,j,dp[i][j]);
        }
    printf("%.4lf\n",dp[0][0]);
    return 0;
}