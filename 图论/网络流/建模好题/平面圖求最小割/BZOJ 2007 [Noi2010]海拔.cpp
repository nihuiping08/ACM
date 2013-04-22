/*

分析：平面圖最小割轉化為最短路。

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

const int MAXN = 505*505;
const int MAXM = MAXN*16;

int po[MAXN],tol,n,m,s,t;
int dis[MAXN];
bool use[MAXN];

struct Edge{
    int y,val,next;
}edge[MAXM];

struct node{
    int x;
    int val;
    node(){}
    node(int _x,int _val):x(_x),val(_val){}
    friend bool operator < (node a,node b){
        return a.x>b.x;
    }
};

priority_queue<node> q;

void add(int x,int y,int val){
    edge[++tol].y = y;
    edge[tol].val = val;
    edge[tol].next = po[x];
    po[x] = tol;
}

int dijkstra(){
    memset(dis,0x7f,sizeof(dis));

    q.push(node(s,0));
    dis[s] = 0;

    while(q.size()){
        node p = q.top();
        q.pop();
        int x = p.x;
        if(p.val>dis[x])
            continue;
        if(x==t)
            return p.val;
        for(int i=po[x];i;i=edge[i].next){
            int y = edge[i].y;
            int cur = edge[i].val+dis[x];
            if(cur<dis[y]){
                dis[y] = cur;
                q.push( node(y,cur) );
            }
        }
    }
    while(true)
        ;
    return -1;
}

int id(int x,int y){
    return x*n-n+y;
}

void init(){
    RD(n);
    int val;
    s = n*n+1;
    t = s+1;

    /******************************************/

    rep1(i,n){
        RD(val);
        add( s,id(1,i),val );
    }
    rep1(i,n-1){
        rep1(j,n){
            RD(val);
            add( id(i,j),id(i+1,j),val );
        }
    }
    rep1(i,n){
        RD(val);
        add( id(n,i),t,val );
    }

    /******************************************/

    rep1(i,n){
        RD(val);
        add( id(i,1),t,val );

        rep1(j,n-1){
            RD(val);
            add( id(i,j+1),id(i,j),val );
        }

        RD(val);
        add( s,id(i,n),val );
    }

    /******************************************/

    rep1(i,n)   RD(val);
    rep1(i,n-1){
        rep1(j,n){
            RD(val);
            add( id(i+1,j),id(i,j),val );
        }
    }
    rep1(i,n)   RD(val);

    /******************************************/

    rep1(i,n){
        RD(val);
        rep1(j,n-1){
            RD(val);
            add( id(i,j),id(i,j+1),val );
        }
        RD(val);
    }
}

int spfa(){
    memset(dis,0x7f,sizeof(dis));
    memset(use,false,sizeof(use));
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    while(q.size()){
        int x = q.front();
        q.pop();
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            int y = edge[i].y;
            int tmp = edge[i].val+dis[x];
            if(tmp<dis[y]){
                dis[y] = tmp;
                if(!use[y]){
                    use[y] = true;
                    q.push(y);
                }
            }
        }
    }
    return dis[t];
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    init();
    //cout<<dijkstra()<<endl;
    cout<<spfa()<<endl;

	return 0;
}
