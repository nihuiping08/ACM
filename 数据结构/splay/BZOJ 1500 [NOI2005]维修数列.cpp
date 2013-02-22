/*

题目：
    插入、删除、区间赋值、翻转、求总和、求最大子序列

分析：
    前面的都是比较简单的splay操作，而在求最大子序列的时候，我们需要维护
    lmax,rmax,mmax三个值，每次下沉的时候都需要更新

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

    const int MAXN = 500005;
    const int INF = 1e9;

    int n,m;
    int root,tot;
    int sta[MAXN],top;
    int pre[MAXN],ch[MAXN][2],sz[MAXN],val[MAXN];
    int sum[MAXN];
    int lmax[MAXN],rmax[MAXN],mmax[MAXN];
    bool rev[MAXN],same[MAXN];
    int aa[MAXN];

    inline void update_same(int x,int v){
        if(x==0)    return;
        val[x] = v;
        same[x] = true;
        sum[x] = sz[x]*v;
        mmax[x] = lmax[x] = rmax[x] = max(sum[x],v);
    }

    inline void update_rev(int x){
        if(x==0)    return;
        rev[x] ^= 1;
        swap(lx,rx);
        swap(lmax[x],rmax[x]);
    }

    inline void update(int x){
        sz[x] = sz[lx]+sz[rx]+1;
        sum[x] = sum[lx]+sum[rx]+val[x];
        lmax[x] = max( lmax[lx] , sum[lx]+val[x]+max(0,lmax[rx]) );
        rmax[x] = max( rmax[rx] , sum[rx]+val[x]+max(0,rmax[lx]) );
        mmax[x] = max( mmax[lx] , mmax[rx] );
        mmax[x] = max( mmax[x] , max(0,lmax[rx])+val[x]+max(0,rmax[lx]) );
    }

    inline void push_down(int x){
        if(rev[x]){
            update_rev(lx);
            update_rev(rx);
            rev[x] = 0;
        }
        if(same[x]){
            update_same(lx,val[x]);
            update_same(rx,val[x]);
            same[x] = 0;
        }
    }

    inline int sgn(int x){
        return ch[px][1]==x;
    }

    inline void setc(int y,int d,int x){
        ch[y][d] = x;
        px = y;
    }

    inline void rot(int x,int d){
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

    inline void splay(int x,int goal=0){
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

    inline int get_Kth(int x,int k){
        push_down(x);
        int tmp = sz[lx]+1;
        if(tmp==k)
            return x;
        if(k<tmp)
            return get_Kth(lx,k);
        return get_Kth(rx,k-tmp);
    }

    inline int get_min(int x){
        push_down(x);
        while(lx){
            x = lx;
            push_down(x);
        }
        return x;
    }

    inline void del(int x){
        if(x==0)    return;
        sta[top++] = x;
        del(lx);
        del(rx);
    }

    inline void Delete(){
        int pos,k;
        scanf("%d%d",&pos,&k);
        int x = get_Kth(root,pos);
        int y = get_Kth(root,pos+k+1);
        splay(x);
        splay(y,root);
        del(lrt);
        pre[lrt] = 0;
        lrt = 0;
        update(rt);
        update(root);
    }

    inline void Make_same(){
        int pos,k,v;
        scanf("%d%d%d",&pos,&k,&v);

        int x = get_Kth(root,pos);
        int y = get_Kth(root,pos+k+1);
        splay(x);
        splay(y,root);

        update_same(lrt,v);
        update(rt);
        update(root);
    }

    inline void Make_rev(){
        int pos,k;
        scanf("%d%d",&pos,&k);

        int x = get_Kth(root,pos);
        int y = get_Kth(root,pos+k+1);

        splay(x);
        splay(y,root);

        update_rev(lrt);
    }

    inline void new_node(int &x,int y,int v){
        if(top) x = sta[--top];
        else    x = ++tot;
        ch[x][0] = ch[x][1] = 0;
        val[x] = sum[x] = lmax[x] = rmax[x] = mmax[x] = v;
        rev[x] = same[x] = 0;
        pre[x] = y;
    }

    inline void build(int &x,int y,int l,int r){
        if(l>r) return;
        int mid = (l+r)>>1;
        new_node(x,y,aa[mid]);
        build(lx,x,l,mid-1);
        build(rx,x,mid+1,r);
        update(x);
    }

    inline void Insert(){
        int pos,k;
        scanf("%d%d",&pos,&k);
        rep(i,k)
            RD(aa[i]);

        pos ++;

        int x = get_Kth(root,pos);
        splay(x);
        int y = get_min(rt);
        splay(y,root);

        build(lrt,rt,0,k-1);
        update(rt);
        update(root);
    }

    inline void Get_sum(){
        int pos,k;
        scanf("%d%d",&pos,&k);
        int x = get_Kth(root,pos);
        int y = get_Kth(root,pos+k+1);
        splay(x);
        splay(y,root);
        printf("%d\n",sum[lrt]);
    }

    inline void Get_max(){
        int pos = 1,k = sz[root]-2;
        int x = get_Kth(root,pos);
        int y = get_Kth(root,pos+k+1);
        splay(x);
        splay(y,root);
        printf("%d\n",mmax[lrt]);
    }

    inline void init(){
        root = tot = top = 0;
        ch[0][0] = ch[0][1] = 0;
        pre[0] = sz[0] = 0;
        sum[0] = same[0] = rev[0] = 0;
        lmax[0] = rmax[0] = mmax[0] = -INF;

        new_node(root,0,-1);
        new_node(rt,root,-1);

        update(rt);
        update(root);

        RD(n);
        RD(m);
        rep(i,n)
            RD(aa[i]);

        build(lrt,rt,0,n-1);
        update(rt);
        update(root);
    }

}using namespace Splay;


int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    init();
    char op[20];
    while(m--){
        scanf("%s",op);
        //puts(op);
        if(op[0]=='I')
            Insert();
        else if(op[0]=='D')
            Delete();
        else if(op[0]=='R')
            Make_rev();
        else if(op[0]=='G')
            Get_sum();
        else if(op[2]=='X')
            Get_max();
        else
            Make_same();
    }

	return 0;
}
