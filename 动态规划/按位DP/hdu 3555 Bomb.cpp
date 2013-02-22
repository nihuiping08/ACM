/*

题目：
    给出n，问1到n的数中拥有子串49的数的个数

分析:
    用数组dp[i][3]记录数据，
    dp[i][0]表示长度为i时所有数中不包括子串49以及最低位4的数的总数，
    dp[i][1]表示长度为i时所有数中最低位为4的数且不包括子串49的总数
    dp[i][2]表示长度为i时所有数中拥有子串49的数的总数
    所以状态转移为
        dp[i][0] = dp[i-1][0]*9+8*dp[i-1][1];
        dp[i][1] = dp[i-1][0]+dp[i-1][1];
        dp[i][2] = dp[i-1][2]*10+dp[i-1][1];

    统计的时候，每次从高位开始往下统计，每次高位的数字乘以dp[i-1][2]，
    若已经出现过了49，诸如xxx49abcd的时候，所以abcd要分别乘以该位长度下的
    dp值。

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 25;

long long dp[X][3],n,ans;

int main()
{
    freopen("sum.in","r",stdin);

    dp[0][0] = 1;
    dp[0][1] = dp[0][2] = 0;
    for(int i=1;i<X;i++)
    {
        dp[i][0] = dp[i-1][0]*9+8*dp[i-1][1];
        dp[i][1] = dp[i-1][0]+dp[i-1][1];
        dp[i][2] = dp[i-1][2]*10+dp[i-1][1];
    }
    int ncase;
    cin>>ncase;
    while(ncase--)
    {
        cin>>n;
        n++;
        int len = 0;
        int d[X] = {0};
        while(n)
        {
            d[++len] = n%10;
            n /= 10;
        }
        ans = 0;
        bool ok = false;
        for(int i=len;i;i--)
        {
            ans += dp[i-1][2]*d[i];
            if(ok)
                ans += d[i]*(dp[i-1][0]+dp[i-1][1]);
            else if(!ok&&d[i]>4)
                ans += dp[i-1][1];
            if(d[i]==9&&d[i+1]==4)
                ok = true;
        }
        cout<<ans<<endl;
    }
    return 0;
}
