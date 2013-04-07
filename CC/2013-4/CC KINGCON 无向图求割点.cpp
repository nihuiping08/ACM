/*

題目：
    求無向圖的割點
分析：
    tarjan算法。。。

*/
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

/******** program ********************/

const int MAXN = 3005;

int map[MAXN][MAXN];
int ans[MAXN],st[MAXN],dfn[MAXN],low[MAXN],n,m,depth;

void dfs(int x){
    dfn[x] = low[x] = ++ depth;
    rep(y,n){
        if(map[x][y]==1){
            map[x][y] = map[y][x] = 2;
            if(!dfn[y]){
                dfs(y);
                low[x] = min(low[x],low[y]);
                if(low[y]>=dfn[x])
                    ans[x] ++;
            }else
                low[x] = min(low[x],dfn[y]);
        }
    }
}

char str[12];
int INT(){
    scanf("%s",str);
    int ans = 0;
    for(int i=0;str[i];i++)
        ans = ans*10+str[i]-'0';
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase,k,x,y;
    RD(ncase);
    while(ncase--){
        RD3(n,m,k);
        rep(i,n){
            rep(j,n)
                map[i][j] = 0;
            dfn[i] = ans[i] = 0;
        }

        while(m--){
            x = INT();
            y = INT();
            map[x][y] = map[y][x] = 1;
        }
        dfs(0);
        ans[0] --;
        int tmp = 0;
        rep(i,n)
            if(ans[i]>0)
                tmp ++;
        printf("%d\n",tmp*k);
    }

	return 0;
}
