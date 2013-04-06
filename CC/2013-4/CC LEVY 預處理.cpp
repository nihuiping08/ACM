/*

題目：
    找出有多少個n = p+2*q的素數對(p,q)
分析：
    素數加預處理

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
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

/******** program ********************/

const int MAXN = 10005;

int p[MAXN],tot;
bool use[MAXN];
int ans[MAXN];

void init(){
    for(int i=2;i<MAXN;i++){
        if(!use[i]){
            p[++tot] = i;
            for(int j=i+i;j<MAXN;j+=i)
                use[j] = true;
        }
    }
}

void solve(){
    init();
    rep1(i,tot)
        rep1(j,tot)
            if(p[i]+2*p[j]<MAXN)
                ans[p[i]+2*p[j]] ++;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    solve();
    int ncase;
    RD(ncase);
    while(ncase--){
        int n;
        RD(n);
        printf("%d\n",ans[n]);
    }

	return 0;
}
