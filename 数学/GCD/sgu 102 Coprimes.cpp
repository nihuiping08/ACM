#include <iostream>
#include <cstdio>

using namespace std;

int n;

int gcd(int a,int b)
{
    if(!a)
        return b;
    return gcd(b%a,a);
}

int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        int ans = 0;
        for(int i=1;i<=n;i++)
            if(gcd(i,n)==1)
                    ans++;
        printf("%d\n",ans);
    }
    return 0;
}
