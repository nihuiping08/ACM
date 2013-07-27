/*

题目：横和竖的两种多米诺骨牌放在平面上，去掉一些多米诺骨牌，使得横和竖不相互重叠。问最少需要去掉多少。
分析：最大独立集

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

const int MAXN = 1005;

int a[MAXN][MAXN],b[MAXN][MAXN];
int ma[MAXN][MAXN],ym[MAXN];
bool use[MAXN];
int n,m;

struct node{
    int x,y;
}pa[MAXN],pb[MAXN];

bool dfs(int x){
    rep1(y,m){
        if(ma[x][y]&&!use[y]){
            use[y] = true;
            if(ym[y]==-1||dfs(ym[y])){
                ym[y] = x;
                return true;
            }
        }
    }
    return false;
}

void hungry(){
    memset(ym,-1,sizeof(ym));
    int ret = 0;
    rep1(i,n){
        memset(use,false,sizeof(use));
        if(dfs(i))
            ret ++;
    }
    cout<<n+m-ret<<endl;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m,n||m){
        int x,y;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));

        rep1(i,n){
            RD2(x,y);
            x ++;
            y ++;
            pa[i].x = x;
            pa[i].y = y;
            a[x][y] = a[x+1][y] = i;
        }

        memset(ma,0,sizeof(ma));
        rep1(i,m){
            RD2(x,y);
            x ++;
            y ++;
            if(a[x][y])
                ma[ a[x][y] ][i] =  true;
            if(a[x][y+1])
                ma[ a[x][y+1] ][i] = true;
        }

        hungry();
    }

	return 0;
}
