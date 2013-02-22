/*

题目：
    由数字较大的一方首先开始操作，他可以把自己手中的数减去任意一个质数或者1，
    得到一个新的数，直到谁手中的数先变为0即为获胜者

分析：
    哥德巴赫猜想：大于等于6的偶数可以分解为两个素数相加，大于等于九的数可以分解为
    三个素数相加，但是由于2是素数，若是奇数的话，可以由2+(n-2)得到，若n-2为素数，
    则只需要两次就行了

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
