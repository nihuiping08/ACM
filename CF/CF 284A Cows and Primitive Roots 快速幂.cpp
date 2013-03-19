/*

题目：
    对于素数p，有x-1,x^2-1...x^(p-2)都不整除p，但是x^(p-1) | p，1<=x<p，问
    有多少个这样的x的存在

分析：
    快速幂

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

int p;

int pw(int x,int exp){
    int ans = 1;
    while(exp>0){
        if(exp&1)
            ans = (ans*x)%p;
        x = x*x%p;
        exp >>= 1;
    }
    return ans;
}

bool ok(int n){
    for(int i=1;i<p-1;i++){
        int ret = pw(n,i)-1+p;
        if(ret%p==0)
            return false;
    }
    return (pw(n,p-1)-1+p)%p==0;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>p){
        int ans = 0;
        for(int i=1;i<p;i++)
            if(ok(i))
                ans ++;
        cout<<ans<<endl;
    }

	return 0;
}
