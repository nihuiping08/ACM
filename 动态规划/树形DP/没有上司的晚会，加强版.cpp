#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const int X = 205;

string s,str;
int n;
int dp[X][2];
vector<int> adj[X];
int dup[X][2];

void dfs(int x)
{
    int len = adj[x].size();
    if(!len)
    {
        dp[x][1] = 1;
        dp[x][0] = 0;
        dup[x][0] = dup[x][1] = 1;
        return;
    }
    int y;
    dp[x][0] = 0;
    dp[x][1] = 1;
    dup[x][0] = 1;
    dup[x][1] = 1;
    for(int i=0;i<len;i++)
        dfs(adj[x][i]);
    for(int i=0;i<len;i++)
    {
        y = adj[x][i];

          if((dp[y][1] > dp[y][0] && dup[y][1] == 0)
                || (dp[y][0] > dp[y][1] && dup[y][0] == 0)
                || dp[y][0] == dp[y][1])
            dup[x][0] = 0;
        if(dup[y][0] == 0)
            dup[x][1] = 0;
        dp[x][0] += max(dp[y][0],dp[y][1]);
        dp[x][1] += dp[y][0];
    }
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n,n)
    {
        cin>>s;
        map<string,int> map;
        for(int i=1;i<=n;i++)
            adj[i].clear();
        map[s] = 1;
        int x,y,cnt = 1;
        for(int i=1;i<n;i++)
        {
            cin>>s>>str;
            if(map[s])
                x = map[s];
            else
                x = map[s] = ++cnt;
            if(map[str])
                y = map[str];
            else
                y = map[str] = ++cnt;
            adj[y].push_back(x);
        }
        dfs(1);
        printf("%d ",max(dp[1][0],dp[1][1]));
        if(dp[1][0]>dp[1][1]&&dup[1][0])
            printf("Yes\n");
        else if(dp[1][1]>dp[1][0]&&dup[1][1])
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
