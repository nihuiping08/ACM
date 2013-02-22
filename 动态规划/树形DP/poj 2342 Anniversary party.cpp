/*

��Ŀ��
    ÿλԱ�������붥ͷ��˾ͬʱ�μӾۻᣬȻ��ÿλԱ������һ����ӭ�ȣ�����ΰ���Ա��
    ��ϯ�ۻᣬʹ�û�ӭ�����

������
    �����Ե�����DP��
    dp[0][i] = ��max(dp[0][j],dp[1][j])
    dp[1][i] = a[i] + ��dp[0][j]
    j�Ķ�ͷ��˾����i��
    �������������������Ե�Ҫ������boss��ʼ���µݹ顣

*/
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 6001;
const int inf = 1e9;

vector<int> adj[X];
int dp[2][X],a[X],n;
int in[X];

void dfs(int x)
{
   int len = adj[x].size();
   int y,a0 = 0,a1 = a[x];
   for(int i=0;i<len;i++)
        dfs(adj[x][i]);
    for(int i=0;i<len;i++)
    {
        y = adj[x][i];
        a0 += max(dp[1][y],dp[0][y]);
        a1 += dp[0][y];
    }
    dp[0][x] = max(dp[0][x],a0);
    dp[1][x] = max(dp[1][x],a1);
}

int main()
{
    freopen("sum.in","r",stdin);
    int x,y;
    while(cin>>n>>a[1],n||a[1])
    {
        for(int i=2;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            adj[i].clear();
        memset(in,0,sizeof(in));
        for(int i=1;i<n;i++)
        {
            scanf("%d%d",&x,&y);
            adj[y].push_back(x);
            in[x]++;
        }
        memset(dp,0,sizeof(dp));
        int v;
        for(int i=1;i<=n;i++)
            if(!in[v = i])
                break;
        dfs(v);
        printf("%d\n",max(dp[0][v],dp[1][v]));
    }
    return 0;
}
