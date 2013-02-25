/*

题目：
    需要求一棵树，然后选一个点出发，然后遍历所有的点再回到出发点，每个
    有权值，边有边权，问如何选择这棵树，使得边权最小
分析：
    prim算法求最短路。
    松弛条件是w[x]+w[y]+2*edge[i].w < dis[y]
    由于点数比较多，所以我们需要用堆优化prim来做

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

const int MAXN = 1e4+5;
const int MAXM = 2e5+5;

int dis[MAXN],val[MAXN];
int po[MAXN],tol;
bool use[MAXN];
int root,n,m;

struct qq{
    int x,y,next;
    int w;
}edge[MAXM];

struct node{
    int x,dis;
    node(){}
    node(int _x,int _d):x(_x),dis(_d){}
    friend bool operator < (node a,node b){
        return a.dis>b.dis;
    }
};

priority_queue<node> q;


void add(int x,int y,int w){
    edge[++tol].x = x;
    edge[tol].y = y;
    edge[tol].w = w;
    edge[tol].next = po[x];
    po[x] = tol;
}

void prim(){
    int ans = 0;
    memset(use,false,sizeof(use));
    memset(dis,0x3f,sizeof(dis));
    q.push(node(root,val[root]));
    dis[root] = val[root];
    while(q.size()){
        node pre = q.top();
        q.pop();
        int x = pre.x;
        if(use[x])
            continue;
        use[x] = 1;
        ans += pre.dis;
        for(int i=po[x];i;i=edge[i].next){
            int y = edge[i].y;
            int tmp = val[x]+val[y]+2*edge[i].w;
            if(!use[y]&&dis[y]>tmp){
                dis[y] = tmp;
                q.push(node(y,dis[y]));
            }
        }
    }
    cout<<ans<<endl;
}

int main(){

#ifndef ONLINE_JUDGE
  freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    cin>>n>>m;
    int Min = 1e9;
    REP(i,1,n+1){
        scanf("%d",&val[i]);
        if(val[i]<Min)
            Min = val[root = i];
    }
    int x,y,w;
    while(m--){
        scanf("%d%d%d",&x,&y,&w);
        add(x,y,w);
        add(y,x,w);
    }
    prim();

	return 0;
}
