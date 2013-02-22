/*

��Ŀ��
    ��һ���ʱ����k��С��Trible������ֻ�ܻ�һ�죬������֮ǰ������i��С���
    ����Ϊp[i]���ʵ�m�죨����m��֮ǰ��ȫ�����ĸ��ʡ���С������ܹ�����n-1�������

������
    �����������⣬����kֻС���໥�������������һֻС���Լ����ĺ����m��֮��ȫ
    �����ĸ���dp[m]���𰸾�Ϊdp[m]^k��
    ���ǣ�
    m = 1������Ϊp[0]����û�����º��
    m = i������һ��С��������i�������ʱ�򣬼���i��С���Ҫ�ڵ�i�춼��������
    i��С���Լ����ǵĺ��ֻ�ܹ����i-1�죬��ȫ���ʹ�ʽ��
    dp[i] = p[0]+p[1]*f[i-1]+p[2]*f[i-1]^2+...+p[n-1]*f[i-1]^(n-1)

    ����p[j]*f[i-1]^j����ʾ��һ���С��������j�������Ҫ��i��ȫ����������j��
    ����ֱַ��ǣ��ѵڶ��쿴����j��С��ĵ�һ�죬�൱�������⣬Ȼ���Ҫ��
    i-1����������j��С���໥���������Ե��ƹ�ʽ�������뵽��

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int X = 1005;

double p[X],dp[X];
int n,k,m;

int main(){
    freopen("sum.in","r",stdin);
    int ncase,cnt = 0;
    cin>>ncase;
    while(ncase--){
        cin>>n>>k>>m;
        for(int i=0;i<n;i++)
            cin>>p[i];
        dp[0] = 0;
        dp[1] = p[0];
        for(int i=2;i<=m;i++){
            dp[i] = p[0];
            for(int j=1;j<n;j++)
                dp[i] += p[j]*pow(dp[i-1],j);
        }
        dp[m] = pow(dp[m],k);
        printf("Case #%d: %.7lf\n",++cnt,dp[m]);
    }
    return 0;
}
