/*

������dp����һ����dp[i][j][k]��i��¼���ǵ�ǰ��λ�ã�j��¼����i��û��ѡ�����λ�ã�
k��ʾ��ǰi�ǼӵĻ��Ǽ���״̬�����Կ����Ƴ�4��״̬ת�Ʒ���

*/
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int P = 150005;

int dp[P][2][2];//dp[i][j][k],i��ʾ��ǰ��λ�ã�j��ʾi��û��ѡ��k��ʾ��ǰi��״̬
int s[P],n;

int main()
{
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++)
        scanf("%d",&s[i]);
    memset(dp,0,sizeof(dp));

    dp[1][1][1] = s[1];
    dp[1][1][0] = -s[1];
    dp[1][0][1] = 0;
    dp[1][0][0] = 0;

    for(int i=2;i<=n;i++)
    {
        dp[i][0][0] = max(dp[i-1][0][0],dp[i-1][1][0]);
        dp[i][0][1] = max(dp[i-1][0][1],dp[i-1][1][1]);
        dp[i][1][0] = max(dp[i-1][0][1],dp[i-1][1][1])-s[i];
        dp[i][1][1] = max(dp[i-1][0][0],dp[i-1][1][0])+s[i];
    }
    printf("%d\n",max(max(dp[n][0][0],dp[n][0][1]),max(dp[n][1][0],dp[n][1][1])));
    return 0;
}
