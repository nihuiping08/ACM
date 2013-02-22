/*

题目：
    对于一棵树n个节点进行剪枝，保留m个树枝，每条边上有一些苹果，
    现在要使得留下来的苹果数目最大，问最大是多少

分析：
    树上DP，由于是完全二叉树，先预处理出有向边，然后对于该树进行
    状态转移，
    dp[x][i] = max(dp[l][i-1]+w[l],dp[r][i-1]+w[r],
                max(dp[l][j]+dp[r][i-j-2]+w[l]+w[r]));

*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

const int X = 105;

int map[X][X],n,m;
bool use[X];
vector<int> a[X],b[X];
int dp[X][X];

void dfs(int x){
    use[x] = true;
    int len = b[x].size();
    if(!len)
        return;
    int l = b[x][0];
    int r = b[x][1];
    dfs(l);
    dfs(r);
    dp[x][1] = max(map[x][l],map[x][r]);
    int temp = map[x][l]+map[x][r];
    for(int i=2;i<=m;i++){
        dp[x][i] = max(dp[l][i-1]+map[x][l],dp[r][i-1]+map[x][r]);
        for(int j=0;j<i-1;j++){
            dp[x][i] = max(dp[x][i],
                        dp[l][j]+dp[r][i-j-2]+temp);
        }
    }
}

void make_tree(int x){
    use[x] = true;
    int len = a[x].size();
    for(int i=0;i<len;i++){
        int y = a[x][i];
        if(!use[y]){
            make_tree(y);
            b[x].push_back(y);
        }
    }
}

int main(){
    freopen("sum.in","r",stdin);
    int x,y,z;
    while(cin>>n>>m){
        for(int i=1;i<=n;i++){
            a[i].clear();
            b[i].clear();
        }
        memset(map,0,sizeof(map));
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&x,&y,&z);
            a[x].push_back(y);
            a[y].push_back(x);
            map[x][y] = map[y][x] = z;
        }
        memset(use,false,sizeof(use));
        memset(dp,0,sizeof(dp));

        make_tree(1);
        dfs(1);
        cout<<dp[1][m]<<endl;
    }
    return 0;
}
