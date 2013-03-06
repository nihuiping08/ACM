/*

题目：有两个箱子，分别有a,b个球，现在从一个箱子往另一个箱子移动球，每次
移动只能够是另一个箱子球的个数，问能不能够使得其中一个箱子空。
分析：我们可以从(0,n)往前面推，发现gcd(a,b)跟(a,b)的状态是一样的。所以
我们可以先对(a,b)分别除掉他们的最大公约数，然后判断a+b是否是2^k形式即可

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

int gcd(int x,int y){
    if(x==0)    return y;
    if(y==0)    return x;
    return gcd(y%x,x);
}

int solve(int n,int m){
    if(n==0 || m==0)
        return 0;
    int g = gcd(n,m);
    n /= g;
    m /= g;
    if((n+m)&1)
        return -1;

    int ans = 0;
    int t = n+m;
    while(t>1){
        if(t&1)
            return -1;
        ans ++;
        t >>= 1;
    }
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,m;
    while(RD2(n,m)!=EOF)
        printf("%d\n",solve(n,m));

	return 0;
}
