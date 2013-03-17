/*

题目：
    支持三种操作：
    1.区间相加
    2.区间翻转
    3.区间最大值

分析：
    splay操作。。。

*/
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

    const int MAXN = 50005;

    int pre[MAXN],ch[MAXN][2],sz[MAXN];
    int val[MAXN],Max[MAXN],rev[MAXN];
    int add[MAXN];
    int tot,root;

    inline void update(int x){
        if(!x)  return;
        sz[x] = sz[lx]+sz[rx]+1;
        if(sz[0]) puts("sz [0] = 0 !");
        Max[x] = max(val[x]+add[x],max( Max[lx],Max[rx]));
    }

    inline void update_add(int x,int v){
        if(!x)  return;
        add[x] += v;
        Max[x] += v;
        val[x] += v;
    }

    inline void push_down(int x){
        if(rev[x]){
            swap(lx,rx);
            //swap(Max[lx],Max[rx]);
            if(lx)  rev[lx] ^= 1;
            if(rx)  rev[rx] ^= 1;
            rev[x] = 0;
        }
        if(add[x]){
            update_add(lx,add[x]);
            update_add(rx,add[x]);
            add[x] = 0;
        }
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

    inline void splay(int x,int goal){ // ok
        if(!x)  return;
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
        if(tmp==k)
            return x;
        if(k<tmp)
            return get_Kth(lx,k);
        return get_Kth(rx,k-tmp);
    }

    inline void dfs(int x){
        if(x){
            cout<<x<<": "<<lx<<" "<<rx<<" "<<add[x]<<" "<<val[x]<<" "<<Max[x]<<endl;
            dfs(lx);
            dfs(rx);
        }
    }

    inline void Add(){
        int x,y,z;
        RD3(x,y,z);

        splay( get_Kth(root,x) , 0 );
        splay( get_Kth(root,y+2),root );

        update_add(lrt,z);

        update(rt);
        update(root);

        //dfs(lrt);
    }

    inline void Rve(){
        int x,y;
        RD2(x,y);

        splay( get_Kth(root,x),0 );
        splay( get_Kth(root,y+2),root );

        rev[lrt] ^= 1;
    }

    inline void Ask(){
        int x,y;
        RD2(x,y);

        splay( get_Kth(root,x),0 );
        splay( get_Kth(root,y+2),root );

        printf("%d\n",Max[lrt]);
    }

    inline void new_node(int &x,int y){ // ok
        x = ++tot;
        val[x] = Max[x] = rev[x] = add[x] = 0;
        px = y;
        lx = rx = 0;
        sz[x] = 1;
    }

    inline void build(int &x,int y,int l,int r){ // ok
        if(l>r) return;
        int mid = (l+r)>>1;
        new_node(x,y);
        build(lx,x,l,mid-1);
        build(rx,x,mid+1,r);
        update(x);
    }

    inline void init(){ // ok
        Max[0] = -1e9;
        new_node(root,0);
        new_node(rt,root);
        update(rt);
        update(root);
    }

    inline void solve(){
        init();

        int n,m,op;
        RD2(n,m);
        build(lrt,rt,1,n);
        update(lrt);
        update(rt);
        update(root);

        while(m--){
            RD(op);
            //cout<<"op = "<<op<<endl;
            if(op==1)       Add();
            else if(op==2)  Rve();
            else            Ask();
            //dfs(root);
        }
    }

};

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    Splay::solve();

	return 0;
}
