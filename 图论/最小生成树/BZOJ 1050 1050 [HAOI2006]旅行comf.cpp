/*

題目：
    找出從a到b的最大邊與最小邊比值最小的路徑
分析：
    類似于kruskal的方式，先對邊排序，然後用并查集合併，若s,t在同一個
    集合里，更新答案

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

#define lx(x) (x<<1)
#define rx(x) (x<<1|1)
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

const int MAXN = 505;
const int MAXM = 10005;
const int INF = 1e9;

int fa[MAXN];
int n,m;

struct node{
    int x,y,val;
    friend bool operator < (node a,node b){
        return a.val<b.val;
    }
    void read(){
        RD3(x,y,val);
    }
}edge[MAXM];

int find_set(int x){
    if(x!=fa[x])
        fa[x] = find_set(fa[x]);
    return fa[x];
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD2(n,m)){
        int s,t;
        rep(i,m)
            edge[i].read();
        RD2(s,t);
        sort(edge,edge+m);
        ll ans_x = 1,ans_y = INF;
        rep(i,m){
            rep1(j,n)
                fa[j] = j;
            REP(j,i,m-1){
                int x = find_set(edge[j].x);
                int y = find_set(edge[j].y);
                if(x==y)
                    continue;
                fa[x] = y;
                if(find_set(s)==find_set(t)){
                    if(ans_x*edge[j].val<ans_y*edge[i].val)
                        ans_x = edge[i].val , ans_y = edge[j].val;
                    break;
                }
            }
        }
        if(ans_y==INF)
            puts("IMPOSSIBLE");
        else{
            int tmp = __gcd(ans_x,ans_y);
            if(tmp==ans_x)
                cout<<ans_y/tmp<<endl;
            else
                cout<<ans_y/tmp<<"/"<<ans_x/tmp<<endl;
        }
    }

	return 0;
}
