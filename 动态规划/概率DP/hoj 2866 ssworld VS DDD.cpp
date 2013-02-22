/*

题意： 2个人分别有AB的血数，轮流扔骰子，数小的自减一血，平的不变，谁先到减0，
谁输，问A赢的概率。

题解： 考虑平局的出现对局面没有影响，因此把平局规约到非平局里即可，对于每一次
p1表示A赢，p2表示B赢，p=1-p1-p2表示平局，A赢的概率为p1+p*p1+p^2*p1+…p^n*p1,
n->无穷，即a=q1/(1-p);b=q2/(1-p)；

然后在他们一定会分出胜负的情况下就可以dp了：

   dp[i][j]=dp[i][j-1]*a+dp[i-1][j]*b;

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 2005;

double dp[X][X];
double a[7],b[7];
int n,m;

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n>>m)
    {
        for(int i=0;i<6;i++)
            scanf("%lf",&a[i]);
        for(int i=0;i<6;i++)
            scanf("%lf",&b[i]);
        double x = 0,y = 0;
        for(int i=0;i<6;i++)
            for(int j=i+1;j<6;j++)
                x += a[i]*b[j];
        for(int i=0;i<6;i++)
            for(int j=0;j<i;j++)
                y += a[i]*b[j];
        for(int i=0;i<=n;i++)
            for(int j=0;j<=m;j++)
                dp[i][j] = 0;
        double tie = 1-x-y;
        x /= (1-tie);
        y /= (1-tie);
        dp[0][0] = 1.0;
        for(int i=0;i<=n;i++)
            for(int j=0;j<=m;j++)
            {
                if(i&&j<m)
                    dp[i][j] += x*dp[i-1][j];
                if(j&&i<n)
                    dp[i][j] += y*dp[i][j-1];
            }
        double ans = 0;
        for(int i=0;i<n;i++)
            ans += dp[i][m];
        printf("%.6lf\n",ans);
    }

    return 0;
}
