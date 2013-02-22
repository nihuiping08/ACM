/*

���⣺ 2���˷ֱ���AB��Ѫ�������������ӣ���С���Լ�һѪ��ƽ�Ĳ��䣬˭�ȵ���0��
˭�䣬��AӮ�ĸ��ʡ�

��⣺ ����ƽ�ֵĳ��ֶԾ���û��Ӱ�죬��˰�ƽ�ֹ�Լ����ƽ���Ｔ�ɣ�����ÿһ��
p1��ʾAӮ��p2��ʾBӮ��p=1-p1-p2��ʾƽ�֣�AӮ�ĸ���Ϊp1+p*p1+p^2*p1+��p^n*p1,
n->�����a=q1/(1-p);b=q2/(1-p)��

Ȼ��������һ����ֳ�ʤ��������¾Ϳ���dp�ˣ�

   dp[i][j]=dp[i][j-1]*a+dp[i-1][j]*b;

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 2005;

double dp[X][X];
double a[7],b[7];
int n,m;

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n>>m)
    {
        for(int i=0;i<6;i++)
            scanf("%lf",&a[i]);
        for(int i=0;i<6;i++)
            scanf("%lf",&b[i]);
        double x = 0,y = 0;
        for(int i=0;i<6;i++)
            for(int j=i+1;j<6;j++)
                x += a[i]*b[j];
        for(int i=0;i<6;i++)
            for(int j=0;j<i;j++)
                y += a[i]*b[j];
        for(int i=0;i<=n;i++)
            for(int j=0;j<=m;j++)
                dp[i][j] = 0;
        double tie = 1-x-y;
        x /= (1-tie);
        y /= (1-tie);
        dp[0][0] = 1.0;
        for(int i=0;i<=n;i++)
            for(int j=0;j<=m;j++)
            {
                if(i&&j<m)
                    dp[i][j] += x*dp[i-1][j];
                if(j&&i<n)
                    dp[i][j] += y*dp[i][j-1];
            }
        double ans = 0;
        for(int i=0;i<n;i++)
            ans += dp[i][m];
        printf("%.6lf\n",ans);
    }

    return 0;
}
