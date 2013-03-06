/*

题目：构造一个欧拉回路
分析：dfs。。。

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
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 2e5+5;

vector<int> vec[MAXN];
map<int,int> ma;
int ha[MAXN];
bool use[MAXN];
int ans[MAXN],top;
int id[MAXN];
int n;

void dfs(int x){
    use[x] = true;
    foreach(i,vec[x]){
        int y = vec[x][i];
        if(use[y])
            continue;
        dfs(y);
    }
    ans[++top] = ha[x];
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int m;
    int x,y;
    RD(m);
    while(m--){
        RD2(x,y);
        if(ma[x]==0){
            ma[x] = ++n;
            ha[n] = x;
        }
        if(ma[y]==0){
            ma[y] = ++n;
            ha[n] = y;
        }
        x = ma[x];
        y = ma[y];
        vec[x].pb(y);
        vec[y].pb(x);
        id[x] ++;
        id[y] ++;
    }
    int root = 1;
    rep1(i,n)
        if(id[i]&1){
            root = i;
            break;
        }
    dfs(root);
    printf("%d",ans[1]);
    for(int i=2;i<=n;i++)
        printf(" %d",ans[i]);
    puts("");

	return 0;
}
