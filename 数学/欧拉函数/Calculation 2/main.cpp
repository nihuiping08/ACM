/*

题目：
    输出与n不互质的数的和

分析：
    欧拉函数，欧拉函数求的是与n互质的数的和，用它来减就行了


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
