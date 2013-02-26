/*

分析：
    动态计算LCP。

    静态的话，可以用后缀数组来计算，但是对于动态的话就无能为力了。。。
    如果用询问来计算LCP的话，会TLE的，所以我们可以想到用二分+hash来计
    算。但是计算hash的话，由于是动态并且是区间统计问题，所以我们可以用
    splay节点表示字符，并且记录以该节点为根的子树所在的区间的字符串的
    hash值，判断是否相等就行了。。。

    hash函数的选取，用RKhash：
    hash[a,b] = ch[a]*1+ch[a+1]*27+...+ch[b]*27^(b-a)

    需要注意的是：
    1.对于首字符都不同的话，直接输出0
    2.短字符串可能是长字符串的前缀

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
#define REP(i,a,b) for(int i=a;i<b;i++)
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

    const int MAXN = 1e5+10;
    char str[MAXN];
    const int MOD = 9875321;

    int ch[MAXN][2],pre[MAXN],sz[MAXN];
    int ha[MAXN],val[MAXN];
    int p[MAXN];
    int root,tot;

    inline void update(int x){ // ok
        sz[x] = sz[lx]+sz[rx]+1;
        if(sz[0])   puts("error !!! sz[0] != 0");
        ha[x] = ll(ha[lx]+(ll)val[x]*p[ sz[lx] ]+(ll)ha[rx]*p[ sz[lx]+1 ])%MOD;
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
        setc(y,!d,ch[x][d]);
        if(z)   setc(z,sgn(y),x);
        px = z;
        setc(x,d,y);
        update(y);
    }

    inline void splay(int x,int goal=0){ // ok
        if(!x)
            return;
        while(px!=goal){
            int y = px;
            int z = py;
            if(z==goal){
                rot(x,!sgn(x));
                break;
            }
            if(lz==y){
                ly==x?rot(y,1):rot(x,0);
                rot(x,1);
            }
            else{
                ry==x?rot(y,0):rot(x,1);
                rot(x,0);
            }
        }
        update(x);
        if(goal==0)
            root = x;
    }

    inline int get_Kth(int x,int k){ // ok

        int tmp = sz[lx]+1;
        if(tmp==k)  return x;
        return k<tmp?get_Kth(lx,k):get_Kth(rx,k-tmp);
    }

    inline int get_Min(int x){ // ok
        while(lx)   x = lx;
        return x;
    }

    inline void new_node(int &x,int y,int c){ // ok
        x = ++tot;
        ha[x] = val[x] = c;
        px = y;
        lx = rx = 0;
    }

    inline void build(int &x,int y,int l,int r){ // ok
        if(l>r) return;
        int mid = (l+r)>>1;
        new_node(x,y,str[mid]-'a'+1);
        build(lx,x,l,mid-1);
        build(rx,x,mid+1,r);
        update(x);
    }

    void dfs(int x){ // ok
        if(x){
            cout<<x<<" "<<lx<<" "<<rx<<" "<<sz[x]<<" "<<char(val[x]+'a'-1)<<endl;
            dfs(lx);
            dfs(rx);
        }
    }

    inline void init(){ // ok
        //memset(ch,0,sizeof(ch));
        //memset(sz,0,sizeof(sz));
        //memset(pre,0,sizeof(pre));
        //memset(ha,0,sizeof(ha));

        p[0] = 1;
        for(int i=1;i<MAXN;i++)
            p[i] = (ll)p[i-1]*27%MOD;

        root = tot = 0;
        new_node(root,0,0);
        new_node(rt,root,0);

        update(rt);
        update(root);

        gets(str);
        int n = strlen(str);
        build(lrt,rt,0,n-1);
        update(rt);
        update(root);
    }

    int has(int x,int y){ // ok
        splay( get_Kth(root,x) );
        splay( get_Kth(root,y+2),root );
        return ha[lrt];
    }

    inline void Q(){
        //puts("-------------------------------");
        int x,y;
        scanf("%d%d",&x,&y);
        if(x==y){
            printf("%d\n",tot-2-y+1);
            return;
        }

        if(x>y) swap(x,y);

        splay( get_Kth(root,x+1) );
        int tmp = val[root];
        splay( get_Kth(root,y+1) );

        //dfs(root);
        //cout<<"k = "<<get_Kth(root,y+1)<<endl;

        //cout<<"tot  = "<<tot<<endl;
        //cout<<dx<<" "<<dy<<endl;
        if(val[root] != tmp ){
            puts("0");
            return;
        }
        //cout<<"-------  "<<tot-2-y+1<<endl;
        if(tot-2-y+1==1){
            puts("1");
            return;
        }
        //debug;

        int len = tot-2-y;
        if( has(x,x+len)==has(y,y+len) ){
            printf("%d\n",tot-2-y+1);
            return;
        }

        //debug;
        int l = 1,r = tot-2-y;
        while(l<=r){
            int mid = (l+r)>>1;
            if(has(x,x+mid)==has(y,y+mid))
                l = mid+1;
            else
                r = mid-1;
        }
        printf("%d\n",l);
    }

    inline void R(){ // ok
        char s[2];
        int x;
        scanf("%d%s",&x,s);
        splay( get_Kth(root,x+1) );
        val[root] = s[0]-'a'+1;
        update(root);
    }

    inline void I(){ // ok
        int x;
        char s[2];
        scanf("%d%s",&x,s);

        x = get_Kth(root,x+1);
        //cout<<"dsadsa "<<x<<endl;
        splay(x);
        int y = get_Min(rt);
        splay(y,root);
        //cout<<y<<endl;

        new_node(lrt,rt,s[0]-'a'+1);
        update(lrt);
        update(rt);
        update(root);
        //dfs(root);
    }

    inline void solve(){ // ok
        init();
        //dfs(root);
        char op[2];
        int m;
        cin>>m;
        while(m--){
            scanf("%s",op);
            if(op[0]=='Q')      Q();
            else if(op[0]=='R') R();
            else                I();
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
