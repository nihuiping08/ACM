/*

题目：找出长度为n的数x，并且x*x %1e9 = 987654321数的个数
分析：大表之后发现，在1e9范围类满足的数的个数为8个，当超过了1e10的
数量级的时候就相当于在那8个数前面填上一些数。

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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif
    /*
    ll n = 1e9;
    ll goal = 987654321;
    for(ll i=1;i<=n;i++)
        if(i*i%n==goal)
            cout<<i<<endl;

    1e9范围类
    111111111
    119357639
    380642361
    388888889
    611111111
    619357639
    880642361
    888888889

    超出的话，就相当于在上面的数后面填0

    */

    int n;
    while(cin>>n){
        if(n<9)         puts("0");
        else if(n==9)   puts("8");
        else{
            cout<<72;
            n -= 10;
            rep(i,n)
                putchar('0');
            puts("");
        }
    }

	return 0;
}
