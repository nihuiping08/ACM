/*

��Ŀ��
    ����һ����n���Ӳ�����n���������ѡ��һ����������������n������p��ʱ�򣬿�
    ��ת��Ϊn/p����ʽ������n���䣬���ڸ���n�������ܹ�ת��Ϊ1����������

������
    ������Կ���һ�����״̬ת������ÿ��������n����������һ���ȸ����¼�������
    ȫ������ʽ�����ѷ��ֵ��ƹ�ϵ���£�
    dp[x] = 1+dp[x]*( (sum[x]-p[x])/sum[x] )+�� (dp[x/y] / sum[x] ),yΪx������
    ���ӡ�
    1��ʾΪ�Ѿ�ת����һ�Σ������ѡ���Ĳ���x�������ӣ���x���仯��������
    dp[x]*( (sum[x]-p[x])/sum[x] )����yΪx�������ӣ�ת��Ϊ�� (dp[x/y] / sum[x] )

    �㷨��ʵ�֣����ü��仯��������ʵ�ָ��㷨����������Ϊ�޸Ĺ���ɸ�����Ѳ�����
    x�������ĸ���ͳ�Ƴ������Լ���x���������Ӵ��ڶ�ά�����ע�⵽
    2*3*5*7*11*13*17*19>1000000�������Եڶ�ά���Կ���9�����ˡ��������ÿ�����
    �˵�dp[x]�������ٴ�������������еĲ������ݶ�һ��~~��

*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

const int X = 1000002;

int use[X];
int sum[X];
int p[X];
int div[X][9],top[X];
int n;
double dp[X];

void init(){
    memset(use,0,sizeof(use));
    memset(top,0,sizeof(top));
    for(int i=2;i<X;i++){
        if(use[i])
            sum[i] = sum[i-1];
        else{
            top[i] = 1;
            div[i][0] = i;
            sum[i] = sum[i-1]+1;
            for(int j=i+i;j<X;j+=i){
                use[j] = true;
                div[j][top[j]++] = i;
            }
        }
    }
}

double f(int x){
    if(use[x])
        return dp[x];
    use[x] = true;
    if(x==1)
        return dp[x] = 0;
    double ans = sum[x];
    for(int i=0;i<top[x];i++)
        ans += f(x/div[x][i]);
    return dp[x] = ans/top[x];
}

int main(){
    freopen("sum.in","r",stdin);
    init();
    int ncase,cnt = 0;
    cin>>ncase;
    memset(use,false,sizeof(use));
    while(ncase--){
        cin>>n;
        printf("Case %d: %.10lf\n",++cnt,f(n));
    }
    return 0;
}
