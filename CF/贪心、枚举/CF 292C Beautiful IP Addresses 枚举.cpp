/*

题目：给出n个数字，问这n个数字能够组成的回文IP地址的个数
分析：
    1.枚举。。。
    2.dfs...

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

const int MAXN = 260;

vector<int> d[MAXN];
int sta[MAXN],a[15],ary[15],n,need;
int ans[5][100000],tot;
bool good[MAXN],use[15];

bool cal(int x){
    int y = x;
    while(y){
        int t = y%10;
        if(!use[t]) return false;
        d[x].pb(t);
        sta[x] |= 1<<t;
        y /= 10;
    }
    if(x==0){
        d[x].pb(0);
        sta[0] = 1;
        good[0] = 1;
    }

    reverse( d[x].begin(),d[x].end() );
    return true;
}

bool paa(int top){
    int l = 1;
    while(l<=top)
        if(ary[l++]!=ary[top--])
            return false;
    return true;
}

void solve(int x,int y,int z){
    int top = 0;
    foreach(i,d[x])
        ary[++top] = d[x][i];
    foreach(i,d[y])
        ary[++top] = d[y][i];
    foreach(i,d[z])
        ary[++top] = d[z][i];

    rep(i,256) if(good[i]){
        foreach(j,d[i])
            ary[top+j+1] = d[i][j];

        if( paa( top+d[i].size() ) ){
            ans[0][++tot] = x;
            ans[1][tot] = y;
            ans[2][tot] = z;
            ans[3][tot] = i;
        }
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD(n);
    rep1(i,n){
        RD(a[i]);
        need |= 1<<a[i];
        use[ a[i] ] = true;
    }

    rep(i,256)
        good[i] = cal(i);
    rep(i,256) if(good[i])
        rep(j,256) if(good[j])
            rep(k,256) if(good[k])
                if( (sta[i]|sta[j]|sta[k])==need )
                    solve(i,j,k);

    cout<<tot<<endl;
    rep1(i,tot)
        printf("%d.%d.%d.%d\n",ans[0][i],ans[1][i],ans[2][i],ans[3][i]);

	return 0;
}
