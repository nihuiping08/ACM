#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <cstdio>
#include <utility>
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
#define Clear(x) memset(x,0,sizeof(x))
/*

#pragma comment(linker, "/STACK:1024000000,1024000000")

int size = 256 << 20; // 256MB
char *p = (char*)malloc(size) + size;
__asm__("movl %0, %%esp\n" :: "r"(p) );

*/

/******** program ********************/

const int MAXN = 65540;

struct BIT{
    int c[MAXN];
    inline void init(){
        Clear(c);
    }
    inline int lowbit(int x){
        return x & -x;
    }
    inline void modify(int x,int val){
        if(x==0)return;
        while(x<MAXN){
            c[x] += val;
            x += lowbit(x);
        }
    }
    inline void update(int x,int y,int val){
        modify(x,val);
        modify(y,-val);
    }
    inline int ask(int x){
        int ans = 0;
        while(x>0){
            ans += c[x];
            x -= lowbit(x);
        }
        return ans;
    }
    inline int ask(int x,int y){
        return ask(x)-ask(y);
    }
}bit;

int a[MAXN],b[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n;
    while(cin>>n){
        bit.init();

        rep1(i,n){
            RD(a[i]);
            b[i] = a[i];
        }

        sort(b+1,b+n+1);
        int len = unique(b+1,b+n+1)-b;

        ll ans = 0;
        for(int i=n;i;i--){
            int id = lower_bound(b+1,b+len+1,a[i])-b+1;
            ans += bit.ask(id-1);
            bit.modify(id,1);
        }

        cout<<ans<<endl;
    }

	return 0;
}
