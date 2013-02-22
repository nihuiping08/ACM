/*

题目：
    给出n个数，现在选出一组数使得ai,aj的gcd>=m且j>i，使得这组数
    最多

分析：
    DP，但是是真么转移方程呢？
    dp[i]表示以数i结尾的长度，再利用另一个数组记录每个输入数的因
    子，实现转移方程，dp[a[i]] = max(dp[a[i]]])+1

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxm = 1e6+10;
const int maxn = 1005;
const int inf = ~0U>>1;

int n,m;
int dp[maxm],a[maxm];

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m){
        memset(dp,0,sizeof(dp));

        for(int j=0;j<n;j++){
            int x,top = 0;
            int temp = 0;
            scanf("%d",&x);
            for(int i=1;i*i<=x;i++)
                if(x%i==0){
                    if(i>=m)
                        a[top++] = i;
                    if(x/i>=m)
                        a[top++] = x/i;
                }
            for(int i=0;i<top;i++)
                temp = max(temp,dp[a[i]]);
            temp ++;
            for(int i=0;i<top;i++)
                dp[a[i]] = temp;
        }
        int ans = 0;
        for(int i=0;i<maxm;i++)
            ans = max(ans,dp[i]);
        cout<<ans<<endl;
    }
    return 0;
}
