/*

题目：
    能不能再指定的重量下装满硬币，使得硬币的价值最少

分析：
    完全背包问题

*/
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int X = 10005;
const int inf = 1e9;

int dp[X],n,m,e,f,v[X],w[X];

int main()
{
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    while(ncase--)
    {
        cin>>e>>f>>n;
        for(int i=1;i<=n;i++)
            scanf("%d%d",&v[i],&w[i]);
        m = f-e;
        for(int i=0;i<=m;i++)
            dp[i] = inf;
        dp[0] = 0;
        for(int i=1;i<=n;i++)
            for(int j=w[i];j<=m;j++)
                dp[j] = min(dp[j],dp[j-w[i]]+v[i]);
        dp[m]==inf?printf("This is impossible.\n"):printf("The minimum amount of money in the piggy-bank is %d.\n",dp[m]);
    }
    return 0;
}
