/*

给出一个数列ai，询问区间中出现多少对不同的数	

离线处理。跟上一题差不多，只不过这里需要对于他的下一位以及下一位的下一位进行操作。

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
#define Clear(x) memset(x,0,sizeof(x))
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/

const int MAXN = 2100000;

int ans[MAXN];
int last[MAXN],po[MAXN],a[MAXN];
int n,m,c;

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
    inline int ask(int x){
        int ans = 0;
        while(x>0){
            ans += c[x];
            x -= lowbit(x);
        }
        return ans;
    }
}bit;

struct node{
    int x,y,id;
    friend bool operator < (node a,node b){
        return a.x<b.x;
    }
}q[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase = 0;
    while(~RD3(n,c,m)){
        ncase?puts("----------------------"):ncase = 1;
        bit.init();
        memset(po,0,sizeof(po));

        rep1(i,n)
            RD(a[i]);
        for(int i=n;i;i--){
            last[i] = po[a[i]];
            po[a[i]] = i;
        }

        rep1(i,n){
            bit.modify(last[i],1);
            bit.modify(last[last[i]],-1);
        }

        rep(i,m){
            RD2(q[i].x,q[i].y);
            q[i].id = i;
        }

        sort(q,q+m);

        memset(ans,-1,sizeof(ans));
        int now = 1;
        rep(i,m){
            int l = q[i].x;
            int r = q[i].y;
            while(now<l){
                bit.modify( last[now],-1 );
                bit.modify( last[ last[now] ],1 );
                //bit.modify( last[ last[ last[now] ] ],-1 );
                now ++;
            }
            ans[ q[i].id ] = bit.ask( r );
        }
        rep(i,m)
            printf("%d\n",ans[i]);
    }

	return 0;
}
