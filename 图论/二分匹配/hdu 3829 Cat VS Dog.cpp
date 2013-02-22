/*

题目：
    有人喜欢猫不喜欢狗，有人喜欢狗不喜欢猫，现在给出所有人的喜好，并且给猫狗编号，
    去掉一部分猫狗使得最多人高兴

分析:
    由于每个人的喜好有可能不一样，可以把人分为两种，X部喜欢猫不喜欢狗，Y部喜欢狗不喜欢猫，
    当i喜欢的动物恰好是j不喜欢的动物，或者i不喜欢的动物j喜欢，则他们之间连线，然后求的最大
    匹配ret，p-ret/2即为所求

*/
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int X = 1005;

int ym[X],n,c,d;
char a[X][5],b[X][5];
bool use[X];
bool map[X][X];

bool dfs(int u)
{
    int t;
    for(int v=1;v<=n;v++)
    {
        if(map[u][v]&&!use[v])
        {
            use[v] = true;
            t = ym[v];
            if(t==-1||dfs(t))
            {
                ym[v] = u;
                return true;
            }
        }
    }
    return false;
}

void hungry()
{
    memset(ym,-1,sizeof(ym));
    int ret = 0;
    for(int u=1;u<=n;u++)
    {
        memset(use,false,sizeof(use));
        if(dfs(u))
            ret++;
    }
    cout<<n-ret/2<<endl;
}

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    while(cin>>c>>d>>n)
    {
        memset(map,false,sizeof(map));
        for(int i=1;i<=n;i++)
            scanf("%s%s",a[i],b[i]);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(strcmp(a[i],b[j])==0||strcmp(b[i],a[j])==0)
                    map[i][j] = true;
        hungry();
    }


    return 0;
}
