/*

题目：
    ACboy很喜欢玩一种战略游戏，在一个地图上，有N座城堡，每座城堡都有一定的宝物，
    在每次游戏中ACboy允许攻克M个城堡并获得里面的宝物。但由于地理位置原因，有些
    城堡不能直接攻克，要攻克这些城堡必须先攻克其他某一个特定的城堡。
    Input
    每个测试实例首先包括2个整数，N,M.(1 <= M <= N <= 200);在接下来的N行里，每行包
    括2个整数，a,b. 在第 i 行，a 代表要攻克第 i 个城堡必须先攻克第 a 个城堡，如果
    a = 0 则代表可以直接攻克第 i 个城堡。b 代表第 i 个城堡的宝物数量, b >= 0。当
    N = 0, M = 0输入结束。


Output
    对于每个测试实例，输出一个整数，代表ACboy攻克M个城堡所获得的最多宝物的数量。

分析：
    树上背包，由于城堡想要攻陷，必须得要有一个可以直接攻克的城堡，所以可以以城堡0
    作为根节点，然后m值加一进行树上背包，转移方程为
    dp[x][i] = max(dp[x][i],dp[x][i-j]+dp[y][j]);要攻陷y必须先攻陷x

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 205;

int adj[X][X];
int top[X];
int n,m,a[X];
int dp[X][X];

void dfs(int x)
{
    int len = top[x];
    int y;
    for(int i=1;i<=m;i++)
        dp[x][i] = a[x];
    dp[x][0] = 0;
    for(int k=0;k<len;k++)
    {
        y = adj[x][k];
        dfs(y);
        for(int i=m;i;i--)
            for(int j=1;j<i;j++)
                dp[x][i] = max(dp[x][i],dp[x][i-j]+dp[y][j]);
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n>>m,n||m)
    {
        int x;
        memset(top,0,sizeof(top));
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&x,&a[i]);
            adj[x][top[x]++] = i;
        }
        m++;
        memset(dp,0,sizeof(dp));
        dfs(0);
        cout<<dp[0][m]<<endl;
    }
    return 0;
}
