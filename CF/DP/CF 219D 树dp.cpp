/*

题目：
	给出一棵有向树，选择一个节点（A），通过反置一些边的方向，使得从该节点出发能够走完整棵树，问最少需要
	反置多少条边，并且把符合条件的节点输出。

分析：
	两次dfs。
	第一次求出假设节点1出发需要反置边的数目。
	第二次，从节点1出发，如果当前节点为y，他的父亲节点为x，则以x作为A时，所需代价为val[x]-cost+1-cost
	（由于节点x已经算出了以x为A时的代价，所以现在算y时，只需要把y到x的代价减掉即可）

*/
#include <set>
#include <map>
#include <list>
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
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)
#define All(vec) vec.begin(),vec.end()
#define MP make_pair
#define PII pair<int,int>
#define PQ priority_queue
#define cmax(x,y) x = max(x,y)
#define cmin(x,y) x = min(x,y)
#define fir first
#define sec second

/******** program ********************/

const int MAXN = 5e5+5;

int po[MAXN],tol;
int dp[MAXN];

struct node{
    int y,next;
    int d;
}edge[MAXN];

void add(int x,int y,int d){
    edge[++tol].y = y;
    edge[tol].d = d;
    edge[tol].next = po[x];
    po[x] = tol;
}

int dfs_1(int x,int fa){
    int ans = 0;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)continue;
        ans += dfs_1(y,x)+edge[i].d;
    }
    return ans;
}

void dfs_2(int x,int fa){
    for(int i=po[x];i;i=edge[i].next){
        int y =  edge[i].y;
        if(y==fa)continue;
        dp[y] = dp[x]+1-edge[i].d-edge[i].d;
        dfs_2(y,x);
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n;
    while(cin>>n){
        int x,y;
        memset(po,0,sizeof(po));
        tol = 1;
        REP(i,2,n){
            RD2(x,y);
            add(x,y,0);
            add(y,x,1);
        }

        dp[1] = dfs_1(1,0);
        //cout<<"rev = "<<dp[1]<<endl;
        dfs_2(1,0);
        int t = *min_element(dp+1,dp+n+1);

        cout<<t<<endl;
        rep1(i,n)
            if(dp[i]==t)
                printf("%d ",i);
        puts("");
    }

	return 0;
}
