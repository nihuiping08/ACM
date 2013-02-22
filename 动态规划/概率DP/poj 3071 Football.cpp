/*

题目：
    现有n轮比赛，每轮比赛都将淘汰一半的人，原来有2^n

分析：
    hint中已经暗示了dp方程

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 135;

int n;
double dp[X][X];
double map[X][X];

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n,n!=-1)
    {
        int size = 1<<n;
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++)
                scanf("%lf",&map[i][j]);
        memset(dp,0,sizeof(dp));
        for(int i=0;i<size;i++)
            dp[0][i] = 1.0;
        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<size;j++)
            {
                dp[i][j] = 0;
                int num = 1<<(i-1);
                int temp = ((j>>(i-1))^1)<<(i-1);
                for(int k=temp;k<temp+num;k++)
                    dp[i][j] += dp[i-1][k]*map[j][k];
                dp[i][j] *= dp[i-1][j];
            }
        }
        int pos = 0;
        for(int i=1;i<size;i++)
            if(dp[n][i]>dp[n][pos])
                pos = i;
        cout<<pos+1<<endl;
    }
    return 0;
}
