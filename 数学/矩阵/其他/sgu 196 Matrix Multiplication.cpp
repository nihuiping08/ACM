/*

题目：
    给出无向图边的关系，转化为邻接矩阵A，求A* X A，A*表示转置矩阵

分析：
    我们直到，无向图转化为矩阵之后，A* = A
    假设B[i,j] = sigma_k ( A[i,k]*A[k,j] )
    ans = sigma_i ( sigma_j ( B[i,j] ) )
        = sigma_i ( sigma_j ( sigma_k( A[i,k]*A[k,j] )))
        = sigma_k ( sigma_i(A[i,k]) * sigma(B[k,j]))

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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 10005;

int deg[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int x,y,n,m;
    RD2(n,m);
    while(m--){
        RD2(x,y);
        deg[x] ++;
        deg[y] ++;
    }

    ll ans = 0;
    for(int i=1;i<=n;i++)
        ans += deg[i]*deg[i];
    cout<<ans<<endl;

	return 0;
}
