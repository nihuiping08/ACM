/*

给出一个串s，现在问有多少个不同的串的起始子串为a，终止子串为b

字符串hash。

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

const ll seed = 1447;
const int MAXN = 2005;

ll ha[MAXN],pw[MAXN];

ll getHash(string a){
    ll ans = 0;
    foreach(i,a)
        ans = ans*seed+a[i];
    return ans;
}

ll cc(int l,int r){
    return ha[r]-ha[l]*pw[r-l];
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    string s,a,b;

    pw[0] = 1;
    rep1(i,MAXN-1)
        pw[i] = pw[i-1]*seed;

    while(cin>>s>>a>>b){
        int len = s.size();

        ha[0] = 0;
        for(int i=1;i<=len;i++)
            ha[i] = ha[i-1]*seed+s[i-1];

        ll x = getHash(a);
        ll y = getHash(b);

        vector<ll> vec;
        rep(i,len){
            if( int(i+a.size())>len)break;
            if( cc(i,i+a.size())!=x )continue;
            for(int j=i;j<len;j++){
                if( int(j+b.size())>len)break;
                if(j+b.size()<i+a.size())continue;
                if(cc(j,j+b.size())==y)
                    vec.pb( cc(i,j+b.size()) );
            }
        }

        sort(All(vec));
        vec.erase( unique(All(vec)),vec.end() );
        cout<<vec.size()<<endl;
    }

	return 0;
}
