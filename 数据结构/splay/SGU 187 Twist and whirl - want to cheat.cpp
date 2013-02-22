/*

题目：对于数列，求m次区间翻转之后的数列

分析：splay简单操作

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
#define RD(n) scanf("%d",&n)

namespace Splay{

#define lx ch[x][0]
#define rx ch[x][1]
#define px pre[x]

#define ly ch[y][0]
#define ry ch[y][1]
#define py pre[y]

#define lz ch[z][0]

#define rt ch[root][1]
#define lrt ch[rt][0]

    const int MAXN = 130015;

    int ch[MAXN][2],pre[MAXN],val[MAXN],sz[MAXN];
    bool rev[MAXN];
    int root,tot;
    int ary[MAXN];
    bool ok;

    inline void update(int x){ // ok
        sz[x] = sz[lx]+sz[rx]+1;
    }

    inline void new_node(int &x,int y,int v){ // ok
        x = ++tot;
        px = y;
        rev[x] = 0;
        lx = rx = 0;
        val[x] = v;
    }

    inline void build(int &x,int y,int l,int r){ // ok
        if(l>r) return;
        int mid = (l+r)>>1;
        new_node(x,y,ary[mid]);
        build(lx,x,l,mid-1);
        build(rx,x,mid+1,r);
        update(x);
    }

    inline void push_down(int x){   // ok
        if(rev[x]==0)   return;
        swap(lx,rx);
        rev[x] = 0;
        rev[lx] ^= 1;
        rev[rx] ^= 1;
    }

    inline int sgn(int x){ // ok
        return ch[px][1]==x;
    }

    inline void setc(int y,int d,int x){ // ok
        ch[y][d] = x;
        px = y;
    }

    inline void rot(int x,int d){ // ok
        int y = px;
        int z = py;
        push_down(y);
        push_down(x);
        setc(y,!d,ch[x][d]);
        if(z)   setc(z,sgn(y),x);
        pre[x] = z;
        setc(x,d,y);
        update(y);
    }

    inline void splay(int x,int goal=0){ // ok
        push_down(x);
        while(px!=goal){
            int y = px;
            int z = py;
            if(z==goal){
                rot(x,!sgn(x));
                break;
            }
            if(lz==y){
                if(ly==x)
                    rot(y,1),rot(x,1);
                else
                    rot(x,0),rot(x,1);
            }
            else{
                if(ry==x)
                    rot(y,0),rot(x,0);
                else
                    rot(x,1),rot(x,0);
            }
        }
        update(x);
        if(goal==0)
            root = x;
    }

    inline int get_Kth(int x,int k){ // ok
        push_down(x);
        int tmp = sz[lx]+1;
        if(tmp==k)  return x;
        if(k<tmp)   return get_Kth(lx,k);
        else        return get_Kth(rx,k-tmp);
    }

    inline void dfs(int x){
        if(x==0)    return;
        push_down(x);
        dfs(lx);
        if(val[x]){
            ok?printf(" "):ok = 1;
            printf("%d",val[x]);
        }
        dfs(rx);
    }

    inline void solve(){
        ok = 0;
        int n,m;
        scanf("%d%d",&n,&m);
        int x,y;

        root = tot = 0;
        ch[0][0] = ch[0][1] = pre[0] = rev[0] = 0;

        ary[0] = 0;
        for(int i=1;i<=n;i++)
            ary[i] = i;
        new_node(root,0,0);
        new_node(rt,root,0);

        build(lrt,rt,1,n);

        while(m--){
            scanf("%d%d",&x,&y);
            x = get_Kth(root,x);
            splay(x);
            y = get_Kth(root,y+2);
            splay(y,root);
            rev[lrt] ^= 1;
        }
        dfs(root);
        puts("");
    }

}using namespace Splay;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    solve();

	return 0;
}
