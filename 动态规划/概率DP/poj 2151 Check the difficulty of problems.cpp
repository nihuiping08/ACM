/*

��Ŀ��
    ��m����Ŀ��t֧���飬Ҫ��ÿ֧��������Aһ���⣬���ҹھ��������ٶ�n����Ŀ��
    ���������Ҫ��ĸ��ʡ�

����:
    dp[k][i][j]��ʾ��k֧���飬��������ǰi����Ŀ������£�����j����ĸ��ʣ�����
    �����dp[k][i][j] = dp[k][i-1][j]*(1-p[k][i])+dp[k][i-1][j-1]*p[k][i]��
    p[k][i]��ʾ��k֧�����i��ĸ���
    Ȼ��������ĿҪ�����ÿ֧��������Aһ�⣬���ҹھ��������ٶ�n���⣬���Կ���
    �����ж�������ٹ���һ��ĸ��ʼ������ж���������˲�����n�������������ĸ���
    ����

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int M = 1001;
const int N = 31;

double dp[M][N][N],a,b;
double p[N],qq[M][N];
int n,m,t;

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>m>>t>>n,m||t||n)
    {
        for(int k=1;k<=t;k++)
        {
            for(int j=1;j<=m;j++)
                scanf("%lf",&p[j]);
            for(int i=0;i<=m;i++)
                for(int j=0;j<=m;j++)
                    dp[k][i][j] = 0.000;
            dp[k][0][0] = 1.000;
            for(int i=1;i<=m;i++)
                for(int j=0;j<=i;j++)
                {
                    if(j==0)
                        dp[k][i][0] = dp[k][i-1][0]*(1.000-p[i]);
                    else
                        dp[k][i][j] = dp[k][i-1][j-1]*p[i]+dp[k][i-1][j]*(1.000-p[i]);
                }
        }
        a = b = 1.000;
        for(int k=1;k<=t;k++)
        {
            a *= (1.000-dp[k][m][0]);
            double temp = 0.0;
            for(int j=1;j<n;j++)
                temp += dp[k][m][j];
            b *= temp;
        }
        printf("%.3lf\n",a-b);
    }
    return 0;
}
