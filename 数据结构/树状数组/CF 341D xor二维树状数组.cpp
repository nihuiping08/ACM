/*

题目：对于一个矩阵，有两种操作：
	1.x0 y0 x1 y1 询问矩阵所有元素异或值
	2.x0 y0 x1 y1 v 矩阵所有元素异或v
	
分析：
	分析x,y的奇偶性。
	
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
/*

#pragma comment(linker, "/STACK:1024000000,1024000000")

int size = 256 << 20; // 256MB
char *p = (char*)malloc(size) + size;
__asm__("movl %0, %%esp\n" :: "r"(p) );

*/

/******** program ********************/

const int MAXN = 1005;

struct BIT{
    ll c[4][MAXN][MAXN];

    inline int mask(int x,int y){
        return (x&1)<<1 | (y&1);
    }
    inline void init(){
        Clear(c);
    }
    inline int lowbit(int x){
        return x & -x;
    }
    inline void modify(int xx,int yy,ll val){
        if(xx==0)return;
        int m = mask(xx,yy);
        for(int x=xx;x<MAXN;x+=lowbit(x))
            for(int y=yy;y<MAXN;y+=lowbit(y))
                c[m][x][y] ^= val;
    }
    inline ll ask(int xx,int yy){
        int m = mask(xx,yy);
        ll ans = 0;
        for(int x=xx;x>0;x-=lowbit(x))
            for(int y=yy;y>0;y-=lowbit(y))
                ans ^= c[m][x][y];
        return ans;
    }

}bit;

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int n,m,a,b,c,d,op;
    ll v;
    while(cin>>n>>m){
        bit.init();
        while(m--){
            RD(op);
            RD4(a,b,c,d);
            if(op==1){
                ll ans = 0;
                ans ^= bit.ask(c,d)^bit.ask(a-1,b-1);
                ans ^= bit.ask(c,b-1)^bit.ask(a-1,d);
                cout<<ans<<endl;
            }else{
                scanf("%I64d",&v);
                bit.modify(a,b,v);
                bit.modify(a,d+1,v);
                bit.modify(c+1,b,v);
                bit.modify(c+1,d+1,v);
            }
        }
    }

    return 0;
}
