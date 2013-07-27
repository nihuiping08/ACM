/*

题目：求sigma(i%a-i%b),0<=i<n;
分析：循环节为lcm(a,b)。想寻找一个循环节。在寻找过程中，模拟一次最远能走的距离。如果n比循环节大时递归
寻找n%lcm，否则直接返回答案

*/
#include <set>
#include <map>
#include <list>
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
#define All(vec) vec.begin(),vec.end()
#define MP make_pair
#define PII pair<int,int>
#define PQ priority_queue
#define cmax(x,y) x = max(x,y)
#define cmin(x,y) x = min(x,y)
#define fir first
#define sec second

/******** program ********************/

ll gcd(ll x,ll y){
    return x==0?y:gcd(y%x,x);
}

ll cc(ll n,ll a,ll b){
    if(n==0)return 0;

    ll sum = 0;
    ll lcm = (ll)a*b/gcd(a,b);

    ll pa = 0,pb = 0;

    for(ll i=0;i<lcm;){
        ll t = min(a-pa,b-pb);

        if(i+t>=n){
            //cout<<"N = "<<n<<" "<<sum+(n-i)*abs(pa-pb)<<endl;
            return sum+(n-i)*abs(pa-pb);
        }
        if(i+t>=lcm){
            sum += abs(pa-pb)*(lcm-i);
            break;
        }
        i += t;

        sum += abs(pa-pb)*t;
        pa = (pa+t)%a;
        pb = (pb+t)%b;
    }

    return cc(n%lcm,a,b)+n/lcm*sum;
}

int cal(int n,int a,int b){
    int sum = 0;
    rep(i,n)
        sum += abs(i%a-i%b);
    return sum;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    while(ncase--){
        int n,a,b;
        cin>>n>>a>>b;
        cout<<cc(n,a,b)<<endl;
        //cout<<cc(n,a,b)<<" "<<cal(n,a,b)<<endl;
    }

	return 0;
}
