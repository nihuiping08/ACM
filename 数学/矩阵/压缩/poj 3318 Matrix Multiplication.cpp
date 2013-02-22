/*

��Ŀ��
    �жϾ���a * b == c

������
    ����һ��
        O(n^3)�㷨��ʾ��TLE,����ԭ������һ��ϡ��������Կ�
    ������˵�ʱ���ж��Ƿ�Ϊ0������ͬ������TLE~~

    ��������
        ѹ���������1*n�ľ���ʹ������Լ��ұ߶����1*n��
    ����Ȼ�������ж��Ƿ���Ⱦ�����~~�����������ѹ���Ļ���
    ����֤ÿ��Ԫ�ص����ԣ��������1*n�ľ����Ҫ�������ԣ���
    ���ʱ�����ȡ�������������(1,2...n)

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 505;
#define debug puts("here");

typedef __int64 ll;

int n;

void mul(ll a[X][X],ll *b){
    ll temp[X] = {0};
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            temp[i] += b[j]*a[j][i];
    for(int i=0;i<n;i++)
        b[i] = temp[i];
}

bool eq(ll a[],ll b[]){
    for(int i=0;i<n;i++)
        if(a[i]!=b[i])
            return false;
    return true;
}

ll a[X][X],b[X][X],c[X][X];
ll q[X],p[X];

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n){
        for(int i=0;i<n;i++)
            q[i] = p[i] = i+1;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%I64d",&a[i][j]);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%I64d",&b[i][j]);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%I64d",&c[i][j]);

        mul(a,p);
        mul(b,p);
        mul(c,q);

        if(eq(p,q))
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
