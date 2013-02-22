/*

��Ŀ��
    �����ֽϴ��һ�����ȿ�ʼ�����������԰��Լ����е�����ȥ����һ����������1��
    �õ�һ���µ�����ֱ��˭���е����ȱ�Ϊ0��Ϊ��ʤ��

������
    ��°ͺղ��룺���ڵ���6��ż�����Էֽ�Ϊ����������ӣ����ڵ��ھŵ������Էֽ�Ϊ
    ����������ӣ���������2�����������������Ļ���������2+(n-2)�õ�����n-2Ϊ������
    ��ֻ��Ҫ���ξ�����

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

bool check(int x)
{
    int len = int(sqrt(x*1.0));
    for(int i=2;i<=len;i++)
        if(x%i==0)
            return false;
    return true;
}

int cal(int x)
{
    if(check(x))
        return 1;
    if(x>=4&&(x%2==0))
        return 2;
    if(check(x-2))
        return 2;
    return 3;
}

int main()
{
    freopen("sum.in","r",stdin);
    int t;
    cin>>t;
    int n,m,a,b;
    while(t--)
    {
        scanf("%d%d",&n,&m);
        a = cal(n);
        b = cal(m);
        if(n>m)
        {
            if(a<=b)
                printf("YES\n");
            else
                printf("NO\n");
        }
        else
        {
            if(a>=b)
                printf("NO\n");
            else
                printf("YES\n");
        }
    }
    return 0;
}
