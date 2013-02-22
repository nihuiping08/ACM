/*

��Ŀ��
    ����n����1��n������ӵ���Ӵ�49�����ĸ���

����:
    ������dp[i][3]��¼���ݣ�
    dp[i][0]��ʾ����Ϊiʱ�������в������Ӵ�49�Լ����λ4������������
    dp[i][1]��ʾ����Ϊiʱ�����������λΪ4�����Ҳ������Ӵ�49������
    dp[i][2]��ʾ����Ϊiʱ��������ӵ���Ӵ�49����������
    ����״̬ת��Ϊ
        dp[i][0] = dp[i-1][0]*9+8*dp[i-1][1];
        dp[i][1] = dp[i-1][0]+dp[i-1][1];
        dp[i][2] = dp[i-1][2]*10+dp[i-1][1];

    ͳ�Ƶ�ʱ��ÿ�δӸ�λ��ʼ����ͳ�ƣ�ÿ�θ�λ�����ֳ���dp[i-1][2]��
    ���Ѿ����ֹ���49������xxx49abcd��ʱ������abcdҪ�ֱ���Ը�λ�����µ�
    dpֵ��

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 25;

long long dp[X][3],n,ans;

int main()
{
    freopen("sum.in","r",stdin);

    dp[0][0] = 1;
    dp[0][1] = dp[0][2] = 0;
    for(int i=1;i<X;i++)
    {
        dp[i][0] = dp[i-1][0]*9+8*dp[i-1][1];
        dp[i][1] = dp[i-1][0]+dp[i-1][1];
        dp[i][2] = dp[i-1][2]*10+dp[i-1][1];
    }
    int ncase;
    cin>>ncase;
    while(ncase--)
    {
        cin>>n;
        n++;
        int len = 0;
        int d[X] = {0};
        while(n)
        {
            d[++len] = n%10;
            n /= 10;
        }
        ans = 0;
        bool ok = false;
        for(int i=len;i;i--)
        {
            ans += dp[i-1][2]*d[i];
            if(ok)
                ans += d[i]*(dp[i-1][0]+dp[i-1][1]);
            else if(!ok&&d[i]>4)
                ans += dp[i-1][1];
            if(d[i]==9&&d[i+1]==4)
                ok = true;
        }
        cout<<ans<<endl;
    }
    return 0;
}
