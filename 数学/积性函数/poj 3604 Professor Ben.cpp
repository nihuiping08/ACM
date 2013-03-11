/*

题目：求n的所有约数个数的立方和
分析：g(n) = sigma( f(d) ),d|n
    我们可以yy证明得到g(n)为积性函数，即g(n*m) = g(n)*g(m)
    所以我们可以对n进行质因数分解
    n = p1^k1 * ... * pm^km
    然后g(n) = PI( f(p1^k1) )
    容易得到
    f(p^k)的约数有1,p,p^2....p^k，约数个数为k+1
    即f(p^k) = 1+2+...+(1+k)
    问题解决。。

*/
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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 2500;
vector<int> prime;
bool use[MAXN];

void init(){
    memset(use,0,sizeof(use));
    for(int i=2;i<MAXN;i++)
        if(!use[i]){
            prime.pb(i);
            for(int j=i+i;j<MAXN;j+=i)
                use[j] = true;
        }
}

void solve(){
    int n;
    RD(n);
    int top = 0;
    ll ans = 1;
    for(int i=0;prime[i]*prime[i]<=n;i++)
        if(n%prime[i]==0){
            ++ top;
            int num = 0;
            while(n%prime[i]==0){
                n /= prime[i];
                num ++;
            }
            ans = ans*(num+1)*(num+2)*(num+1)*(num+2)/4;
        }
    if(n>1)
        ans *= 9;
    cout<<ans<<endl;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    init();
    int ncase;
    cin>>ncase;
    while(ncase--)
        solve();

	return 0;
}
