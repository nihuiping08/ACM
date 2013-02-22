/*

题目：
    在一个环中有n个格子，每个格子的值为ai，距离该格子不足d的所有格子的和对于
    m取余为新的值，问第k次变换后的所有n个格子的值

分析：
    很容易可以构造出一个循环的矩阵出来，但是如果是O(n^3*logn)会TLE。
    我们可以注意到循环矩阵a * b只需要计算a的第一行*b，然后下面的移位均可以得
    到。时间为O(n^2*logn)

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

#define debug puts("here")

#define rep(i,n) for(int i=0;i<n;i++)

#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)

#define pb push_back

const int X = 505;

ll a[X][X],c[X][X];
ll ans[X];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    int n,m,k,d;
    while(~scanf("%d%d%d%d",&n,&m,&d,&k)){
        rep(i,n)
            scanf("%lld",&ans[i]);

        rep(i,n)
            rep(j,n)
                if( (i-j+n)%n<=d || (j-i+n)%n<=d )
                    a[i][j] = 1;
                else
                    a[i][j] = 0;

        while(k>0){
            if(k&1){
                rep(i,n){
                    c[0][i] = 0;
                    rep(j,n)
                        c[0][i] += ans[j]*a[j][i];
                }
                rep(i,n)
                    ans[i] = c[0][i]%m;
            }

            rep(i,n){
                c[0][i] = 0;
                rep(j,n)
                    c[0][i] += a[0][j]*a[j][i];
            }
            rep(i,n)
                rep(j,n)
                    if(i==0)
                        a[i][j] = c[i][j]%m;
                    else
                        a[i][j] = a[i-1][(j-1+n)%n];

            k >>= 1;
        }
        rep(i,n-1)
            printf("%lld ",ans[i]);
        printf("%lld\n",ans[n-1]);
    }
	return 0;
}
