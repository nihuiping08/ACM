/*

题目：
    n个格子，位置从1到n，每个格子有值di。若|i-j| = di，则i和j两个格子
    可以互相交换格子上的数。现在给出一个排列，问能不能够从1到n的排列
    通过交换得到该排列

分析：
    我们对于可以交换的两个格子建立无向边，然后通过tarjan求出一个连通块
    中的数集S，然后判断位置集合S中的所有数是不是都是数集S

*/
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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 105;

vector<int> vec[MAXN];
vector<int> p[MAXN];
int a[MAXN];
int id[MAXN];
int fa[MAXN],dfn[MAXN],low[MAXN],stack[MAXN],bcnt,depth,top;
bool instack[MAXN],use[MAXN];
int n,m;

void dfs(int x){
    dfn[x] = low[x] = ++depth;
    stack[++top] = x;
    instack[x] = true;
    int y;
    foreach(i,vec[x]){
        y = vec[x][i];
        if(dfn[y]==0){
            dfs(y);
            low[x] = min(low[x],low[y]);
        }else if(instack[y])
            low[x] = min(low[x],dfn[y]);
    }
    if(low[x]==dfn[x]){
        ++ bcnt;
        do{
            y = stack[top--];
            fa[y] = bcnt;
            instack[y] = false;
        }while(x!=y);
    }
}

void tarjan(){
    memset(instack,0,sizeof(instack));
    memset(dfn,0,sizeof(dfn));
    top = bcnt = depth = 0;
    for(int i=1;i<=n;i++)
        if(dfn[i]==0)
            dfs(i);
}

bool solve(){
    for(int i=1;i<=n;i++)
        p[fa[i]].pb(i);
    for(int i=1;i<=bcnt;i++){
        memset(use,false,sizeof(use));
        foreach(j,p[i])
            use[p[i][j]] = 1;
        foreach(j,p[i]){
            int x = id[p[i][j]];
            if(use[x]==false)
                return false;
        }
    }
    return true;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n){
        rep1(i,n){
            cin>>a[i];
            id[a[i]] = i;
            vec[i].clear();
            p[i].clear();
        }
        int x;
        rep1(i,n){
            cin>>x;
            if(x+i<=n){
                vec[i].pb(x+i);
                vec[x+i].pb(i);
            }
            if(i-x>0){
                vec[i].pb(i-x);
                vec[i-x].pb(i);
            }
        }
        tarjan();
        solve()?puts("YES"):puts("NO");
    }

	return 0;
}
