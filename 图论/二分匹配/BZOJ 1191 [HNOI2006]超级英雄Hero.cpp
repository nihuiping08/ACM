/*

题目：锦囊与游戏
分析：二分图最大匹配，若本轮没有通过，不能进入下一轮

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
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

const int MAXN = 100005;

vector<int> vec[MAXN];
int ym[MAXN],n,m;
bool use[MAXN];

bool dfs(int x){
    foreach(i,vec[x]){
        int y = vec[x][i];
        if(!use[y]){
            use[y] = true;
            int t = ym[y];
            if(t==-1||dfs(t)){
                ym[y] = x;
                return true;
            }
        }
    }
    return false;
}

void hungry(){
    int ans = 0;
    memset(ym,-1,sizeof(ym));
    rep1(i,n){
        memset(use,false,sizeof(use));
        if(dfs(i))
            ans ++;
        else // 如果本轮游戏没通过，不能进入下一轮
            break;
    }
    cout<<ans<<endl;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD2(m,n);
    int x,y;
    rep1(i,n){
        RD2(x,y);
        vec[i].pb(++x);
        vec[i].pb(++y);
    }
    hungry();

	return 0;
}

