#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int X = 50;

int main()
{
    int dp[X];
    int a,b,c;
    while(scanf("%d%d%d",&a,&b,&c),a||b||c)
    {
        dp[1] = dp[2] = 1;
        for(int i=3;i<X;i++)
            dp[i] = (a*dp[i-1]+b*dp[i-2])%7;
        dp[0] = dp[49];
        printf("%d\n",dp[c%49]);
    }
    return 0;
}
