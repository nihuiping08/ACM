/*

题目：
    每个节点都有bugs，只有把全部bugs打死了才能获得经验，并且每人只能消灭20个
    bugs，给出n-1条边以及每个节点的bugs数目以及他们的相应经验，问如何使得经验
    最大

分析:
    树上背包，由于是从节点1出发，可以分很多支队去别的节点。每个节点得用二维数组
    记录以当前节点i时人数为j的时候的最优解，然后DFS自顶向下，从叶子节点往上逐层
    更新。转移方程为dp[i][j] = dp[i][i-j] + dp[y][j]

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int X = 105;

int p[X],b[X],n,m;
vector<int> adj[X];
bool use[X];
int dp[X][X];

void dfs(int x)
{
    use[x] = true;
    int temp = (b[x]+19)/20;
    for(int i=temp;i<=m;i++)
        dp[x][i] = p[x];
    int y;
    int len = adj[x].size();
    for(int k=0;k<len;k++)
    {
        y = adj[x][k];
        if(use[y])
            continue;
        dfs(y);
        for(int i=m;i>=temp;i--)
            for(int j=1;j+temp<=i;j++)
                dp[x][i] = max(dp[x][i],dp[x][i-j]+dp[y][j]);
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n>>m)
    {
        if(n==-1&&m==-1)
            break;
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&b[i],&p[i]);
            adj[i].clear();
        }
        int x,y;
        for(int i=1;i<n;i++)
        {
            scanf("%d%d",&x,&y);
            adj[y].push_back(x);
            adj[x].push_back(y);
        }
        if(!m)
        {
            puts("0");
            continue;
        }
        memset(dp,0,sizeof(dp));
        memset(use,false,sizeof(use));
        dfs(1);
        cout<<dp[1][m]<<endl;
    }
    return 0;
}
