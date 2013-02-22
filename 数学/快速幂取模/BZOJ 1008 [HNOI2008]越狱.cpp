/*

题目：
	监狱有连续编号为1...N的N个房间，每个房间关押一个犯人，有M种宗教，每个犯人可能信仰其中一种。
	如果相邻房间的犯人的宗教相同，就可能发生越狱，求有多少种状态可能发生越狱

分析：
	我们可以相求相邻的都不同，则问题 = m^n - (m-1)^(n-1)*m，所以直接快速幂求即可
	
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
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back

const int X = 1000005;
const ll mod = 100003;

ll a[X];

ll pw(ll a,ll b){
    ll ret = 1;
    while(b>0){
        if(b&1)
            ret = (ret*a)%mod;
        a = (a*a)%mod;
        b >>= 1;
    }
    return ret;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    ll n,m;
    while(cin>>m>>n){
        ll x = pw(m,n);
        ll y = pw(m-1,n-1);
        y = y*m%mod;
        cout<<(x+mod-y)%mod<<endl;
    }

	return 0;
}
