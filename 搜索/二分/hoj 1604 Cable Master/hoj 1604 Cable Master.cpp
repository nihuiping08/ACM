#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 10005;

long long len[X],n,k;
long long sum;

bool check(long long mid)
{
    long long cnt =0;
    for(int i=0;i<n;i++)
        cnt += len[i]/mid;
    return cnt>=k;
}

void binary()
{
    long long left = 1,right = sum/k;
    long long mid;
    while(left<right)
    {
        mid = (left+right+1)>>1;
        if(mid==0)
        {
            printf("0.00\n");
            return;
        }
        if(check(mid))
            left = mid;
        else
            right = mid-1;
    }
    if(check(left))
        printf("%.2lf\n",left/100.0);
    else
        printf("0.00\n");
}

int main()
{
    freopen("sum.in","r",stdin);
    double x;
    while(cin>>n>>k)
    {
        sum = 0;
        for(int i=0;i<n;i++)
        {
            scanf("%lf",&x);
            len[i] = (long long)(x*100+0.01);
            sum += len[i];
        }
        binary();
    }
    return 0;
}
