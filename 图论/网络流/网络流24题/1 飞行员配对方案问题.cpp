/*

分析：二分图的最大匹配

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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

const int MAXN = 1005;

int map[MAXN][MAXN];
int ym[MAXN];
bool use[MAXN];
int n,m;

bool dfs(int x){
    rep1(y,n){
        if(map[x][y]&&!use[y]){
            int t = ym[y];
            use[y] = true;
            if(t==-1||dfs(t)){
                ym[y] = x;
                return true;
            }
        }
    }
    return false;
}

void hungry(){
    int ret = 0;
    memset(ym,-1,sizeof(ym));
    rep1(i,m){
        memset(use,false,sizeof(use));
        if(dfs(i))
            ret ++;
    }
    if(ret==0){
        puts("No Solution!");
        return;
    }
    cout<<ret<<endl;
    rep1(i,n)
        if(ym[i]!=-1)
            cout<<ym[i]<<" "<<i<<endl;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int x,y;
    while(cin>>m>>n){
        memset(map,0,sizeof(map));
        while(RD2(x,y),x!=-1||y!=-1)// x 外籍1~m,y 英国籍m+1~n
            map[x][y] = 1;
        hungry();
    }

	return 0;
}
