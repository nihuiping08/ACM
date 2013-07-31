/*

求逆序对

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
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/

const int MAXN = 1e6+5;

vector<int> vec[26],t[26];
int top[26];
char s[MAXN];
ll c[MAXN];
int a[MAXN];

void modify(int x,int val){
    for(int i=x;i<MAXN;i+=i&-i)
        c[i] += val;
}

ll ask(int x){
    ll ret = 0;
    for(int i=x;i>0;i-=i&-i)
        ret += c[i];
    return ret;
}

int main(){


    int n;
    while(cin>>n){
        scanf("%s",s);
        rep(i,26){
            vec[i].clear();
            t[i].clear();
        }
        rep(i,n)
            vec[ s[i]-'A' ].pb(i);
        scanf("%s",s);
        rep(i,n)
            t[ s[i]-'A' ].pb(i);
        rep(i,26)
            foreach(j,vec[i])
                a[ vec[i][j] ] = t[i][j];

        memset(c,0,sizeof(c));
        ll ans = 0;
        for(int i=n-1;i>=0;i--){
            ans += ask( a[i] );
            modify( a[i]+1,1 );
        }
        cout<<ans<<endl;
    }

	return 0;
}
