/*

题目：
    给出一棵树，每个节点带有权，每条边有边权。现在要从一个节点出发，最
    后要回到出发点，所走过的距离不超过m，每走过一个节点会得到该节点的
    价值，现在问如何走，使得价值数最大

分析：
    经典的树上背包问题

*/
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 205;

int dp[MAXN][MAXN];
int val[MAXN];
int n,m;

vector<int> vec[MAXN][2];

void dfs(int x,int fa){
    for(int i=0;i<=m;i++)
        dp[x][i] = val[x];

    foreach(k,vec[x][0]){
        int y = vec[x][0][k];
        int tmp = 2*vec[x][1][k];
        if(fa==y)
            continue;
        dfs(y,x);
        for(int i=m;i>=tmp;i--)
            for(int j=0;j+tmp<=i;j++)
                dp[x][i] = max(dp[x][i],dp[x][i-j-tmp]+dp[y][j]);
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int x,y,len;
    while(cin>>n){
        for(int i=1;i<=n;i++){
            vec[i][0].clear();
            vec[i][1].clear();
        }
        for(int i=1;i<=n;i++)
            RD(val[i]);

        for(int i=1;i<n;i++){
            RD3(x,y,len);
            vec[x][0].pb(y);
            vec[x][1].pb(len);
            vec[y][0].pb(x);
            vec[y][1].pb(len);
        }

        memset(dp,0,sizeof(dp));
        int k;
        RD2(k,m);
        dfs(k,0);
        cout<<dp[k][m]<<endl;
    }

	return 0;
}
