#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 105;

double a[X],dp[X][X];
int n,m,l,k;

int main()
{
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    while(ncase--)
    {
        cin>>n>>m>>l>>k;
        memset(a,0,sizeof(a));
        a[k] = 0;
        for(int i=k-1;i>=0;i--)
            a[i] = a[i+1]+n*1.0/(n-i);
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        for(int i=1;i<=m;i++)
            for(int j=1;j<=l;j++)
            {
                double temp = (n-j+1)*1.0/n;
                dp[i][j] = dp[i-1][j]*(j*1.0/n)+dp[i-1][j-1]*(temp);
            }
        printf("%.3lf %.3lf\n",dp[m][l],a[0]);
    }
    return 0;
}
