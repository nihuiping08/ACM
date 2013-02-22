/*

��Ŀ��
    ����һ����ά���ӵ�ͼ��Ȼ��ÿ�λ�������ȥ�����ľ�Ϊ2�������ʷֱ�Ϊ
    pr(����),pd(����),p(ԭ��)������ĳ�˴Ӹ���[1,1]�������ʵ���[n,m]����������
    �Ƕ���

������
    ����������ʽ�������뵽������ʽ����: dp[i][j]��ʾ��[i,j]��������[n,m]������
    ���ġ�
    dp[i][j] = (dp[i][j]+2)*p[i][j]+(dp[i+1][j]+2)*pd[i][j]+(dp[i][j+1]+2)*pr[i][j];
    ���ڵ�ʽ������dp[i][j]������󼴿ɽ����dp[1][1]
    ע�⵱a[i][j] == 1ʱ���ø��Ӳ����������ߣ����Ե�Ҫ���⴦������

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int X = 1005;

double PD[X][X],PR[X][X],P[X][X];
double dp[X][X];
int n,m;

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%lf%lf%lf",&P[i][j],&PR[i][j],&PD[i][j]);
        memset(dp,0,sizeof(dp));
        for(int i=n;i;i--)
            for(int j=m;j;j--){
                double temp = 0;
                if(P[i][j]<1){
                    temp = (2+dp[i+1][j])*PD[i][j]+(2+dp[i][j+1])*PR[i][j]+2*P[i][j];
                    temp /= 1-P[i][j];
                }
                dp[i][j] = temp;
            }
        printf("%.3lf\n",dp[1][1]);
    }
    return 0;
}
