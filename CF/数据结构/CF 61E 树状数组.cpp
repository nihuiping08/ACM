/*

问数列中满足：i<j<k，ai>aj>ak的三元组个数

简单树状数组

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

const int MAXN = 1e6+5;

ll c[MAXN];
ll l[MAXN],r[MAXN];
int a[MAXN],b[MAXN],n;

int lowbit(int x){
    return x & -x;
}

void modify(int x,int val){
    while(x<=n){
        c[x] += val;
        x += lowbit(x);
    }
}

ll ask(int x){
    ll ret = 0;
    while(x>0){
        ret += c[x];
        x -= lowbit(x);
    }
    return ret;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase = 0;
    while(cin>>n){
        ncase?puts("---------------"):ncase = 1;

        map<int,int> ma;
        rep1(i,n){
            RD(a[i]);
            b[i] = a[i];
        }

        sort(b+1,b+n+1);
        int tot = 0 , x;
        rep1(i,n)
            if( ma[b[i]]==0)
                ma[b[i]] = ++tot;

        memset(c,0,sizeof(c));
        rep1(i,n){
            x = ma[a[i]];
            //cout<<a[i]<<" "<<x<<endl;
            modify(x,1);
            l[i] = ask(n)-ask(x);
        }

        memset(c,0,sizeof(c));
        for(int i=n;i;i--){
            x = ma[a[i]];
            modify(x,1);
            r[i] = ask(x-1);
        }
        ll ans = 0;
        for(int i=2;i<n;i++)
            ans += l[i]*r[i];
        /*
        rep1(i,n)
            cout<<l[i]<<" ";
        cout<<endl;
        rep1(i,n)
            cout<<r[i]<<" ";
        cout<<endl;
        */

        cout<<ans<<endl;
    }

	return 0;
}

