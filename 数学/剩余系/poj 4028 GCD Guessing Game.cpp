/*

题目：
    一个人的年龄是y，(1<=y<=n)，要你去猜(你猜的是x的话)。
    如果x==y，结束
    否则告诉你gcd(x,y)
    现在问需要最少尝试多少次才能够得到y
分析：
    把1-n的素数分组，每组的积<=n，答案就是组数
    为什么？我们可以每次猜测每组素数的积：
    1.如果告诉你是1的话，那么只能够继续猜测其他组了 = =。
    2.如果是其中的一个的话，直接猜测 x/d 的倍数。显然这个比情况一更少

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

const int MAXN = 10005;

bool use[MAXN];
vector<int> prime;
int n;

void init(){
    memset(use,0,sizeof(use));
    prime.clear();
    for(int i=2;i<=n;i++)
        if(!use[i]){
            prime.pb(i);
            for(int j=i+i;j<=n;j+=i)
                use[j] = true;
        }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n){
        init();
        int ans = 0;
        int mul = 1;
        int l = 0;
        for(int i=prime.size()-1;i>=l;i--){
            mul = prime[i];
            while(mul*prime[l]<=n)
                mul *= prime[l++];
            ans ++;
        }
        cout<<ans<<endl;
    }

	return 0;
}
