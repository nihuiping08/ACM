/*

题目：
    给出n组铜件的含铜量，以及他们的价格，现在给出m组询问，表示m个顾客需要购买
    的铜件的数目为c，并且要求铜的含量在a-b每个单位范围内。问你如何安排铜件使得
    所需的费用最少。

分析:
    由于所需要的数目是一定的，所以在01背包的基础上增加一维表示当前的数目，由于
    询问的数目很多，所以可以先预处理完再询问。

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 205;
const int maxn = 20005;
#define inf 1e9

int dp[maxn][22];
int con[X],price[X],n,m;

int main()
{
    freopen("sum.in","r",stdin);
    int x,y,ncase = 0;
    while(cin>>n)
    {
        if(ncase)
            cout<<endl;
        else
            ncase = 1;
        for(int i=0;i<n;i++)
            scanf("%d%d",&con[i],&price[i]);
        cin>>m;
        for(int i=0;i<maxn;i++)
            for(int j=0;j<=20;j++)
                dp[i][j] = inf;
        dp[0][0] = 0;
        for(int i=0;i<n;i++)
            for(int j=maxn;j>=con[i];j--)
                for(int k=1;k<=20;k++)
                    dp[j][k] = min(dp[j][k],dp[j-con[i]][k-1]+price[i]);
        while(m--)
        {
            int a,b,c;
            cin>>c>>a>>b;
            x = c*a;
            y = c*b;
            int ans = inf;
            for(int i=x;i<=y;i++)
                ans = min(ans,dp[i][c]);
            ans==inf?printf("impossible\n"):printf("%d\n",ans);
        }
    }
    return 0;
}
