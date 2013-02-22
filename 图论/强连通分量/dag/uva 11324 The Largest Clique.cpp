/*

题目：
    从图中某点出发，求最远能够一次走过多少个节点

分析：
    强连通分量求gcc，然后构造出新图，新图是一个dag，对于dag上用dp求出最长路径即可。
	dp转移方程为
		dp[x] = size[x] + max(dp[y]);  
	缩点后有边x到y的边，记忆化搜索就行了，具体看实现代码

*/
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

const int maxn = 1005;
const int maxm = 50005;

#define debug puts("here");

int dfn[maxn],low[maxn],stack[maxn],father[maxn],bcnt,top,depth;
bool instack[maxn];
int po[maxn],tol,n,m;
int id[maxn];
int dp[maxn];
int sum[maxn];

vector<int> vec[maxn];

struct node{
    int y,next;
}edge[maxm];

void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

void dfs(int x){	//递归实现tarjan算法
    low[x] = dfn[x] = ++depth;
    instack[x] = true;
    stack[++top] = x;
    int y;
    for(int i=po[x];i;i=edge[i].next){
        y = edge[i].y;
        if(!dfn[y]){
            dfs(y);
            low[x] = min(low[x],low[y]);
        }
        else if(instack[y])
            low[x] = min(low[x],dfn[y]);
    }
    if(low[x]==dfn[x]){
        ++bcnt;
        do{
            y = stack[top--];
            instack[y] = false;
            father[y] = bcnt;
        }while(x!=y);
    }
}

void tarjan(){
    memset(low,0,sizeof(low));
    memset(dfn,0,sizeof(dfn));
    top = bcnt = depth = 0;
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            dfs(i);
}

int f(int x){	//记忆化方法求dag上的最长路径
    if(dp[x])
        return dp[x];
    int ans = 0;
    for(int i=0;i<(int)vec[x].size();i++){	//从x的所有边出发，求出最大的路径
        int y = vec[x][i];
        ans = max(ans,f(y));	//转移方程
    }
    dp[x] = ans+sum[x];
    return dp[x];
}

void dag(){
    memset(id,0,sizeof(id));
    memset(sum,0,sizeof(sum));
    memset(dp,0,sizeof(dp));

    for(int i=1;i<=n;i++)
        vec[i].clear();

    for(int x=1;x<=n;x++){		//构造新图
        for(int j=po[x];j;j=edge[j].next){
            int y = edge[j].y;
            if(father[x]!=father[y]){
                vec[father[x]].push_back(father[y]);
                id[father[y]] ++;
            }
        }
        sum[father[x]] ++;	//统计每个缩点后的该节点所包含的所有原图的节点数目
    }

    int ans = 0;
    for(int i=1;i<=bcnt;i++)
        if(!id[i])
            ans = max(f(i),ans);
    cout<<ans<<endl;
}

int main(){
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    while(ncase--){
        cin>>n>>m;
        int x,y;
        memset(po,0,sizeof(po));
        tol = 0;
        while(m--){
            scanf("%d%d",&x,&y);
            add(x,y);
        }
        tarjan();
        dag();
    }
    return 0;
}
