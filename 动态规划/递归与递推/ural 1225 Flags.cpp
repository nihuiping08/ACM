/*

题目：
    现在有三种颜色，对n块旗帜染色，规定：相邻的旗帜不能让相同的颜色，并且
    想要染成蓝色，必须使得与他相邻的两块旗帜一块是白色另一块是红色才行，现
    在问有多少种染色方法

分析：
    相对当前的旗帜染色，那么肯定可以是由i-1不同色而来，或者与i-2不同色而来
    的（i-2不同色的话，就是i-1为蓝色），所以得到斐波那契数列类似的DP

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 55;

long long dp[X];
int n;

int main(){
    freopen("sum.in","r",stdin);
    memset(dp,0,sizeof(dp));
    n = 50;
    dp[1] = dp[2] = 2;
    for(int i=2;i<n;i++)
        dp[i] = dp[i-1]+dp[i-2];

    while(cin>>n)
        cout<<dp[n]<<endl;
    return 0;
}
