/*

题目：
    给出n个石子，每个石子有不同的颜色，而颜色的种类一共有m种，现在问你如何
    去掉最少的石子，使得留下的石子只剩下m堆颜色连续的石子，并且这m堆石子的
    颜色数互不相同（就是说留下m堆石子，分别拥有一种颜色）

分析：
    若使用普通的DP来做的话，数组的维度要开得很大，利用状态压缩的思路可以很好地减少维度
    以及减少冗余的计算。这题由于石子的颜色个数最大只有5，可以用5位的二进制数来表示当前
    的状态，比如01011表示已经用了的颜色种类有1,2，4（从低位往高位数）。比如状态
    f01011可以由f00011,f01001,f01010通过增加相应位置的颜色来表示，当然还可以之前的状态
    已经是这个了。所以f[i][j][k] = min{(f[i-1][j-(1<<k)][p]),f[i-1][j][k]+(a[i]!=k)}，当
    a[i]==k时，可以直接加在后面组成一堆新的石子，但不等时，需要去掉这堆或者把这堆置为新
    的一堆，当然前提是这堆还没有。

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int inf = 1e9;

int dp[101][1<<5][5];
int a[101],n,m;

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n>>m,n||m)
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            a[i]--;
        }
        memset(dp,0x3f,sizeof(dp));
        for(int i=0;i<m;i++)
            dp[1][1<<i][i] = (a[1]!=i);
        for(int i=2;i<=n;i++)
            for(int j=0;j<(1<<m);j++)
                for(int k=0;k<m;k++)
                    if(j&(1<<k))
                    {
                        dp[i][j][k] = min(dp[i][j][k],dp[i-1][j][k]+(a[i]!=k));
                        for(int p=0;p<m;p++)
                            if(k!=p&&(j&(1<<p)))
                                dp[i][j][k] = min(dp[i][j][k],dp[i-1][j-(1<<k)][p]+(a[i]!=k));
                    }
        int ans = inf;
        for(int j=0;j<(1<<m);j++)
            for(int k=0;k<m;k++)
                ans = min(ans,dp[n][j][k]);
        cout<<ans<<endl;
    }
    return 0;
}
