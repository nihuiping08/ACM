/*

題目：矩陣染色
分析：漂浮法染色。

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

#define lx(x) (x<<1)
#define rx(x) (x<<1|1)
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

const int MAXN = 5005;

int n,m,ans;

struct node{
    int lx,ly,rx,ry,col;
    void rd(){
        RD4(lx,ly,rx,ry);
        char op[2];
        scanf("%s",op);
        col = op[0]=='b';
        if(lx>rx)swap(lx,rx);
        if(ly>ry)swap(ly,ry);
    }
}p[MAXN];

void dfs(int lx,int ly,int rx,int ry,int col,int i){
    if(lx>rx||ly>ry)return;
    while(i<=m&&(lx>p[i].rx||ly>p[i].ry||rx<p[i].lx||ry<p[i].ly))
        i ++;
    if(i>m){
        if(col) ans += (rx-lx+1)*(ry-ly+1);
        return;
    }

    if( lx<p[i].lx ){
        dfs(lx,ly,p[i].lx-1,ry,col,i+1);
        lx = p[i].lx;
    }
    if( rx>p[i].rx ){
        dfs( p[i].rx+1,ly,rx,ry,col,i+1 );
        rx = p[i].rx;
    }
    if( ly<p[i].ly )
        dfs( lx,ly,rx,p[i].ly-1,col,i+1 );
    if( ry>p[i].ry )
        dfs( lx,p[i].ry+1,rx,ry,col,i+1 );
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD2(n,m);
    rep1(i,m)
        p[i].rd();
    for(int i=m;i;i--)
        dfs(p[i].lx,p[i].ly,p[i].rx,p[i].ry,p[i].col,i+1);
    cout<<n*n-ans<<endl;
    //cout<<ans<<endl;

	return 0;
}
