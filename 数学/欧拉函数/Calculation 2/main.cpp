/*

��Ŀ��
    �����n�����ʵ����ĺ�

������
    ŷ��������ŷ�������������n���ʵ����ĺͣ���������������


*/
#include <iostream>
#include <cstdio>

using namespace std;

const int mod = 1000000007;

long long n,m;

int eular(long long n)
{
    int ret = 1;
    for(int i=2;i*i<=n;i++)
        if(n%i==0)
        {
            n /= i;
            ret *= i-1;
            while(n%i==0)
                n /= i,ret *= i;
        }
    if(n>1)
        ret *= n-1;

    return ret;
}

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>n,n)
    {
        m = n*(n-1)/2;
        m = m-n*eular(n)/2;
        m %= mod;
        cout<<m<<endl;
    }
    return 0;
}
