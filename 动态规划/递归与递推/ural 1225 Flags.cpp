/*

��Ŀ��
    ������������ɫ����n������Ⱦɫ���涨�����ڵ����Ĳ�������ͬ����ɫ������
    ��ҪȾ����ɫ������ʹ���������ڵ���������һ���ǰ�ɫ��һ���Ǻ�ɫ���У���
    �����ж�����Ⱦɫ����

������
    ��Ե�ǰ������Ⱦɫ����ô�϶���������i-1��ͬɫ������������i-2��ͬɫ����
    �ģ�i-2��ͬɫ�Ļ�������i-1Ϊ��ɫ�������Եõ�쳲������������Ƶ�DP

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 55;

long long dp[X];
int n;

int main(){
    freopen("sum.in","r",stdin);
    memset(dp,0,sizeof(dp));
    n = 50;
    dp[1] = dp[2] = 2;
    for(int i=2;i<n;i++)
        dp[i] = dp[i-1]+dp[i-2];

    while(cin>>n)
        cout<<dp[n]<<endl;
    return 0;
}
