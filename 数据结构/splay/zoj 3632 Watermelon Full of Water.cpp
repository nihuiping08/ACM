/*

题目：
    某人要吃西瓜，第i天的价格为price_i，能够吃的天数为day_i(加上今天)。
    并且在i天买西瓜的话，前面的西瓜得要扔掉。问现在最少需要多少钱使得
    每天都得吃西瓜

分析：
    我们从第n天开始往前面推，假设第i天需要买西瓜，它能够支持的天数从
    第i天开始往后day_i-1天，则我们需要在[i+1,i+day_i]里需要买西瓜。
    所以我们可以用平衡树来维护区间的最小值即可


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

    const int MAXN = 50005;
    const ll INF = 1e15;

    int n,m;
    int root,tot;
    int pre[MAXN],ch[MAXN][2],sz[MAXN];
    ll val[MAXN];
    ll ans[MAXN];
    int price[MAXN],day[MAXN];

    inline void update(int x){
        sz[x] = sz[lx]+sz[rx]+1;
        //if(sz[0])   puts("error");
        ans[x] = min( val[x] , min(ans[lx],ans[rx]) );
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
        setc(y,!d,ch[x][d]);
        if(z)   setc(z,sgn(y),x);
        pre[x] = z;
        setc(x,d,y);
        update(y);
    }

    inline void splay(int x,int goal=0){
        if(x==0)    return;
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
        int tmp = sz[lx]+1;
        if(tmp==k)
            return x;
        if(k<tmp)
            return get_Kth(lx,k);
        return get_Kth(rx,k-tmp);
    }

    inline int get_min(int x){
        while(lx)
            x = lx;
        return x;
    }

    inline void new_node(int &x,int y,ll v){
        x = ++tot;
        val[x] = ans[x] = v;
        lx = rx = 0;
        px = y;
    }

    inline void init(){
        root = tot = 0;
        ch[0][0] = ch[0][1] = 0;
        pre[0] = sz[0] = 0;
        ans[0] = INF;

        new_node(root,0,INF);
        new_node(rt,root,INF);

        update(rt);
        update(root);
    }

    void dfs(int x){
        if(x){
            cout<<x<<" "<<lx<<" "<<rx<<" "<<ans[x]<<" "<<val[x]<<endl;
            dfs(lx);
            dfs(rx);
        }
    }

    inline void Insert(ll x){
        splay( get_min(root) );
        splay( get_Kth(root,2),root );

        new_node(lrt,rt,x);
        update(lrt);
        update(rt);
        update(root);
    }

    inline ll ask(int x,int y){
        if(y>=n) return 0;
        splay( get_Kth(root,x) );
        splay( get_Kth(root,y+2),root );

        return ans[lrt];
    }

    inline void solve(){
        while(cin>>n){
            init();
            rep(i,n)
                RD(price[i]);
            rep(i,n)
                RD(day[i]);

            for(int i=n-1;i>=0;i--){
                //cout<<"-------------------"<<endl;
                //cout<<i<<endl;
                if(day[i]+i>=n){
                    Insert(price[i]);
                    continue;
                }
                if(day[i]==1){
                    ll tmp = ask(1,1);
                    //cout<<"tmp = "<<tmp<<endl;
                    Insert(tmp+price[i]);
                    continue;
                }

                ll tmp = ask(1,day[i]);
                //cout<<"tmp = "<<tmp<<endl;
                tmp += price[i];
                Insert(tmp);
            }
            cout<<ask(1,1)<<endl;
        }
    }

};


int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    Splay::solve();

	return 0;
}
