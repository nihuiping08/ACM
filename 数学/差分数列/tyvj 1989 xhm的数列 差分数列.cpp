/*

��Ŀ��
    ����N������A[1..N]
    ���������ֲ�����
    ����1��ѡ��һ������������[l, r]�������ǵ���ֵȫ������T
    ����2��ѯ��������ĳ��Ԫ��A[i]��ֵ�Ƕ��١�
    Ϊ�˽����Ѷȣ�������ִ��Q1�β���1����ִ��Q2�β���2��

������
    �ⷨ1���߶���OR��״���� ���ز�������
    �ص㽲�ⷨ2:
    �ò��������
    ���������� a_1 a_2 a_3...a_n;
    ������ d_1=a_1
    d_n=a_n-a_(n-1) (n>2)
    �������ǾͿ���ͨ���ۼ� ǰN�� ����D ��֪����A��ֵ��
    ���ǿ���֤��
    �����������[l,r] ���� t ֻ��� d_l + t �� d_(r+1)-t
    �����Ϳ����ˡ�����ʱ�� ���Ӷ�ΪO��N��
    ����Ӽ����������� ���ۼӡ����ó�����A��ֵ

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef __int64 ll;

const int X = 100005;

int n,m,q;
ll a[X],d[X],sum[X];

int main(){
    freopen("sum.in","r",stdin);
    int l,r;
    ll add;
    while(cin>>n>>m>>q){
        a[0] = 0;
        for(int i=1;i<=n;i++){
            scanf("%I64d",&a[i]);
            d[i] = a[i]-a[i-1];
        }
        while(m--){
            scanf("%d%d%I64d",&l,&r,&add);
            d[l] += add;
            d[r+1] -= add;
        }
        sum[0] = 0;
        for(int i=1;i<=n;i++)
            sum[i] = sum[i-1]+d[i];
        while(q--){
            scanf("%d",&l);
            printf("%I64d\n",sum[l]);
        }
    }
    return 0;
}
