/*

題目：
    給出n支球隊的最終比分，問有多少種分數安排的可能

分析：
    純搜索。
    用hash函數來記錄已經搜過的狀態以及該狀態下的安排數目。

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
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

/******** program ********************/

const int MOD = 199997;

int ns[10],sum,n;

struct node{
    int val;
    int num;
    node *next;
    node(int _v,int _n,node* _t):val(_v),num(_n),next(_t){}
};

struct Hash{
    node *adj[MOD];
    node *fin(int val){
        for(node *p=adj[val%MOD];p;p=p->next)
            if(p->val==val)
                return p;
        return NULL;
    }
    void ins(int val,int num){
        adj[val%MOD] = new node(val,num,adj[val%MOD]);
    }
}table[10];

void dfs(int x,int y){
    //cout<<x<<" "<<y<<endl;
    if(x==n){
        if(ns[x]==0)
            sum ++;
        return;
    }
    if(y==n+1){
        if(ns[x])
            return;
        int qq = 0;
        for(int i=x+1;i<=n;i++)
            qq = qq*23+ns[i];
        node *p = table[x].fin(qq);
        if(p)
            sum += p->num;
        else{
            int t = sum;
            dfs(x+1,x+2);
            table[x].ins(qq,sum-t);
            //cout<<qq<<" "<<sum<<" "<<t<<endl;
        }
        return;
    }

    if(ns[x]>=3){
        ns[x] -= 3;
        dfs(x,y+1);
        ns[x] += 3;
    }
    if(ns[x]&&ns[y]){
        ns[x] --;
        ns[y] --;
        dfs(x,y+1);
        ns[x] ++;
        ns[y] ++;
    }
    if(ns[y]>=3){
        ns[y] -= 3;
        dfs(x,y+1);
        ns[y] += 3;
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD(n);
    rep1(i,n)
        RD(ns[i]);

    sort(ns+1,ns+n+1);
    dfs(1,2);
    cout<<sum<<endl;


	return 0;
}
