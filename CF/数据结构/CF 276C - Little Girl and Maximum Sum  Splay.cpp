/*

splay简单区间操作，增加两个额外的节点，然后对于区间[a,b]执行加一操作时，
把第a小的节点splay至根，把第b+2小的节点splay至根（增加了两个节点。。）
然后把根的右儿子的左儿子lazy标记加一。

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

string str;

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

    const int MAXN = 2e5+5;

    int pre[MAXN],sz[MAXN],ch[MAXN][2];
    ll sum[MAXN],add[MAXN];
    int a[MAXN],n,m;
    int tot,root;

    inline void update(int x){
        sz[x] = sz[lx]+sz[rx]+1;
    }

    inline void push_down(int x){
        if(add[x]){
            if(lx)  add[lx] += add[x];
            if(rx)  add[rx] += add[x];
            sum[x] += add[x];
            add[x] = 0;
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
        return k<tmp?get_Kth(lx,k):get_Kth(rx,k-tmp);
    }

    inline void modify(int l,int r){
        int x = get_Kth(root,l);
        int y = get_Kth(root,r+2);
        splay(x);
        splay(y,root);
        add[lrt] ++;
        update(rt);
        update(root);
    }

    inline void new_node(int &x,int y,ll v){
        x = ++tot;
        sum[x] = v;
        add[x] = 0;
        lx = rx = 0;
        pre[x] = y;
    }

    inline void build(int &x,int y,int l,int r){
        if(l>r) return;
        int mid = (l+r)>>1;
        new_node(x,y,0);
        build(lx,x,l,mid-1);
        build(rx,x,mid+1,r);
        update(x);
    }

    inline void dfs(int x){
        if(x){
            push_down(x);
            dfs(lx);
            dfs(rx);
        }
    }

    inline void init(){
        memset(ch,0,sizeof(ch));
        memset(pre,0,sizeof(pre));
        memset(a,0,sizeof(a));
        memset(sum,0,sizeof(sum));
        memset(add,0,sizeof(add));

        root = tot = 0;
        new_node(root,0,0);
        new_node(rt,root,0);
        update(rt);
        update(root);
    }

    void dfs_debug(int x){
        if(x){
            cout<<x<<" "<<lx<<" "<<rx<<endl;
            dfs_debug(lx);
            dfs_debug(rx);
        }
    }

    void solve(){
        init();

        int n,m;
        cin>>n>>m;

        build(lrt,rt,0,n-1);
        update(rt);
        update(root);

        //dfs_debug(root);

        rep(i,n)
            scanf("%d",&a[i]);
        int x,y;
        while(m--){
            //debug;
            scanf("%d%d",&x,&y);
            modify(x,y);
        }

        dfs(root); // 把所有标记下沉

        sort(sum+1,sum+tot+1);
        reverse(sum+1,sum+tot+1);

        sort(a,a+n);
        reverse(a,a+n);

        ll ans = 0;
        rep(i,n)
            ans += a[i]*sum[i+1];
        cout<<ans<<endl;
    }

}using namespace Splay;

int main(){

#ifndef ONLINE_JUDGE
  freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    solve();

	return 0;
}

