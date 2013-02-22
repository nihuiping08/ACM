/*

在2维状态下递推期望 ， 利用期望的公式，

E = x1 * p1 + x2 * p2 + …… xn*pn。

状态转移方程式：
f[i][j] =（f[i][j]+2）* exp[i][j][1] + (f[i+1][j]+2) * exp[i][j][2] +
          (f[i][j+1]+2) * exp[i][j][3]
这个式子左右都有f[i][j]，化简后：
f[i][j] =（(f[i+1][j]+2) * exp[i][j][2] + (f[i][j+1]+2) * exp[i][j][3]+
           2 * exp[i][j][1]）/ （1 - exp[i][j][1]）

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 1005;

double dp[X][X],map[X][X][3];
int n,m;

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n>>m)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                for(int k=0;k<3;k++)
                    scanf("%lf",&map[i][j][k]);
        double temp = 0;
        memset(dp,0,sizeof(dp));
        for(int i=n;i;i--)
            for(int j=m;j;j--)
            {
                if(i==n&&j==m)
                    continue;
                if(map[i][j][0]-1<0)
                {
                    temp = 1+dp[i+1][j]*map[i][j][2]+dp[i][j+1]*map[i][j][1];
                    temp /= (1-map[i][j][0]);
                }
                dp[i][j] = temp;
            }
        printf("%.3lf\n",dp[1][1]*2);
    }
    return 0;
}
