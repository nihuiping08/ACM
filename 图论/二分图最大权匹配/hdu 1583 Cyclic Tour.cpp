/*

题目：
    二分图的最小权匹配

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 155;
const int inf = 1e8;
#define debug puts("here");

int n,m;
int lx[X],ly[X],slack[X],match[X];
bool usex[X],usey[X];
int map[X][X];

bool dfs(int x)
{
    int temp;
    usex[x] = true;
    for(int i=1;i<=n;i++)
        if(!usey[i])
        {
            temp = lx[x]+ly[i]-map[x][i];
            if(!temp)
            {
                usey[i] = true;
                if(match[i]==0||dfs(match[i]))
                {
                    match[i] = x;
                    return true;
                }
            }
            else
                slack[i] = min(slack[i],temp);
        }
    return false;
}

void KM()
{
    memset(ly,0,sizeof(ly));
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++)
    {
        lx[i] = -inf;
        for(int j=1;j<=n;j++)
            lx[i] = max(lx[i],map[i][j]);
    }

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            slack[j] = inf;
        while(true)
        {
            memset(usex,false,sizeof(usex));
            memset(usey,false,sizeof(usey));
            if(dfs(i))
                break;
            int MIN = inf;
            for(int j=1;j<=n;j++)
                if(!usey[j])
                    MIN = min(MIN,slack[j]);
            for(int j=1;j<=n;j++)
                if(usex[j])
                    lx[j] -= MIN;
            for(int j=1;j<=n;j++)
                if(usey[j])
                    ly[j] += MIN;
                else
                    slack[j] -= MIN;
        }
    }
    int ans = 0;
    for(int i=1;i<=n;i++)
    {
        if(map[match[i]][i]==-inf)
        {
            puts("-1");
            return;
        }
        ans += map[match[i]][i];
    }
    cout<<-ans<<endl;
}

int main()
{
    freopen("sum.in","r",stdin);
    int x,y,z;
    while(cin>>n>>m)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                map[i][j] = -inf;
        while(m--)
        {
            scanf("%d%d%d",&x,&y,&z);
            map[x][y] = max(map[x][y],-z);
        }
        KM();
    }
    return 0;
}
