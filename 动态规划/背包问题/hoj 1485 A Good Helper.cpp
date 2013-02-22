#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 1005;

int dp[X];
int x,y,n;
int a[X];

int main()
{
    freopen("sum.in","r",stdin);
    while(cin>>x>>y)
    {
        int sum = 0;
        cin>>n;
        for(int i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
            sum += a[i];
        }
        sort(a,a+n);
        memset(dp,0,sizeof(dp));
        for(int i=n;i;i--)
            for(int j=x;j>=a[i];j--)
                dp[j] = max(dp[j],dp[j-a[i]]+a[i]);
        x = sum-dp[x];
        if(x>y)
        {
            if(x-a[n-1]<=y)
                printf("Need a helper\n");
            else
                cout<<"No"<<endl;
        }
        else
            printf("Yes\n");
    }
    return 0;
}
