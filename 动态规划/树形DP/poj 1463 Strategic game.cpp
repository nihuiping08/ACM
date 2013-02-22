/*

最小边集覆盖问题。如果父母节点不安排士兵把守，儿子必须全得安排士兵把守。
若父母节点安排的话，儿子节点可以安排，可以不安排，所以状态转移方程为
dp[i][0] += dp[j][1]
dp[i][1] += min(dp[j][0],dp[j][1]); //j是i的儿子

*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
#define MAXN 1505
int n,dp[MAXN][2];
vector<int> a[MAXN];
void dfs(int u,int pre){
    int size = a[u].size(),v;
    for(int i=0;i<size;i++){
        v = a[u][i];
        if(v!=pre){
            dfs(v,u);
            dp[u][0] += dp[v][1];
            dp[u][1] += min(dp[v][0],dp[v][1]);
        }
    }
    a[u].clear();
}
int main(){
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    int x,y,z;
    while(cin>>n){
        for(int i=0;i<n;i++){
            scanf("%d:(%d)",&x,&z);
            while(z--){
                scanf("%d",&y);
                a[x].push_back(y);
                a[y].push_back(x);
            }
            dp[x][0] = 0;
            dp[x][1] = 1;
        }
        dfs(0,0);
        printf("%d\n",min(dp[0][0],dp[0][1]));
    }
    return 0;
}
