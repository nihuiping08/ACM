/*

ural 1076

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 205;
const int inf = 1e9;
#define debug puts("here");

int lx[X],ly[X],match[X],n,m;
int map[X][X],slack[X];
bool usex[X],usey[X];

bool dfs(int x)
{
    usex[x] = true;
    for(int i=1;i<=n;i++)
        if(!usey[i])
        {
            int temp = lx[x]+ly[i]-map[x][i];
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
    memset(lx,0,sizeof(lx));
    memset(ly,0,sizeof(ly));
    memset(match,0,sizeof(match));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            lx[i] = max(lx[i],map[i][j]);

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
        for(int j=1;j<=n;j++)
            ans += map[i][j];
        ans -= map[match[i]][i];
    }
    cout<<ans<<endl;
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                scanf("%d",&map[i][j]);
        KM();
    }
    return 0;
}
