/*

��Ŀ��
    ����n��ͭ���ĺ�ͭ�����Լ����ǵļ۸����ڸ���m��ѯ�ʣ���ʾm���˿���Ҫ����
    ��ͭ������ĿΪc������Ҫ��ͭ�ĺ�����a-bÿ����λ��Χ�ڡ�������ΰ���ͭ��ʹ��
    ����ķ������١�

����:
    ��������Ҫ����Ŀ��һ���ģ�������01�����Ļ���������һά��ʾ��ǰ����Ŀ������
    ѯ�ʵ���Ŀ�ܶ࣬���Կ�����Ԥ��������ѯ�ʡ�

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
