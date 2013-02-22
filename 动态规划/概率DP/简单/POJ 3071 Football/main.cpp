#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int X = 130;

double dp[8][X];
double a[X][X];

int main(){
    freopen("sum.in","r",stdin);
    int h;
    while(cin>>h,h!=-1){
        int n = 1<<h;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                scanf("%lf",&a[i][j]);
        for(int i=0;i<n;i++)
            dp[0][i] = 1;
        for(int i=1;i<=h;i++){
            for(int j=0;j<n;j++){
                int len = 1<<(i-1);
                int s = ((j>>(i-1))^1)<<(i-1);
                //cout<<i<<" "<<j<<" "<<len<<" "<<s<<endl;
                dp[i][j] = 0;
                for(int k=s;k<s+len;k++)
                    dp[i][j] += dp[i-1][k]*a[j][k];
                dp[i][j] *= dp[i-1][j];
            }
        }
        int pos = 0;
        for(int i=0;i<n;i++)
            if(dp[h][i]>dp[h][pos])
                pos = i;
        cout<<1+pos<<endl;
    }
    return 0;
}
