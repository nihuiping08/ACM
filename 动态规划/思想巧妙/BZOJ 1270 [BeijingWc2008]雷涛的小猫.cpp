/*

题目：
    给出n棵树，树的高度均为h步，每棵树上挂着一些苹果，一只猫
    可以从一棵树往下跳一步，或者跳到任意别的树，但是高度下
    降d步，猫能从任意一棵树往下跳，问猫能够得到的最多苹果数目

分析：
    DP，三层循环的DP转移方程比较好想，
    dp[i][j] = max( max(dp[k][j-d])),dp[i][j-1])+map[i][j]
    由于数据比较大，三层循环会超时，所以得要压缩成两层循环
    用额外的数组best记录每层高度的最优解，用一维dp记录当前
    位置的最优解，这转移方程可以写为
    dp[i] = max(dp[i],max(best[j-d])) + map[i][j]
    best[j] = max(dp[i])

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 2005;

int map[X][X];
int dp[X],best[X],n,h,d;

int main(){
    freopen("sum.in","r",stdin);
    int x,y;
    while(cin>>n>>h>>d){
        memset(dp,0,sizeof(dp));
        memset(best,0,sizeof(best));
        memset(map,0,sizeof(map));
        for(int i=1;i<=n;i++){
            scanf("%d",&y);
            while(y--){
                scanf("%d",&x);
                map[i][x] ++;
            }
        }
        for(int j=1;j<=h;j++){
            for(int i=1;i<=n;i++){
                if(j>=d)
                    dp[i] = max(dp[i],best[j-d])+map[i][j];
                else
                    dp[i] = dp[i]+map[i][j];
                best[j] = max(best[j],dp[i]);
            }
        }
        cout<<best[h]<<endl;
    }
    return 0;
}
