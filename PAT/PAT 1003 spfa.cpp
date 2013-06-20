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
#define All(vec) vec.begin(),vec.end()
#define MP make_pair
#define PII pair<int,int>

/******** program ********************/

const int MAXN = 505;
const int INF = 1e9;

int q[MAXN*MAXN];
int po[MAXN],tol;
int dis[MAXN];
int term[MAXN];
bool use[MAXN];
vector<int> vec[MAXN];

struct node{
    int y,val,next;
}edge[MAXN*MAXN];

void add(int x,int y,int val){
    edge[++tol].y = y;
    edge[tol].val = val;
    edge[tol].next = po[x];
    po[x] = tol;
}

void spfa(int n,int s,int t){ // 最短路spfa
    rep(i,n)
        dis[i] = INF;
    memset(use,false,sizeof(use));
    dis[s] = 0;
    int head = 0 , tail = 0;
    q[++tail] = s;
    while(head<tail){
        int x = q[++head];
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            int y = edge[i].y;
            if(dis[y]>dis[x]+edge[i].val){ // 遇到更短的

                vec[y].clear(); // 清空
                vec[y].pb(x);

                dis[y] = dis[x]+edge[i].val;
                if(!use[y]){
                    use[y] = true;
                    q[++tail] = y;
                }
            }else if(dis[y]==dis[x]+edge[i].val) // 相同的
                vec[y].pb(x); // 放进去
        }
    }
}

int a,b;

void dfs(int x,int s,int sum){ // dfs回溯即可
    if(x==s){
        a ++;
        b = max(sum,b);
        return;
    }
    use[x] = true;
    foreach(i,vec[x])
        if(!use[ vec[x][i] ])
            dfs(vec[x][i],s,sum+term[ vec[x][i] ]);
    use[x] = false;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    memset(po,0,sizeof(po));
    tol = 0;

    int n,m,s,t;
    RD4(n,m,s,t);
    rep(i,n)
        RD(term[i]);

    int x,y,val;
    while(m--){
        RD3(x,y,val);
        add(x,y,val); // 无向边
        add(y,x,val);
    }
    spfa(n,s,t);

    a = b = 0;

    memset(use,false,sizeof(use));
    dfs(t,s,term[t]);
    cout<<a<<" "<<b<<endl;

	return 0;
}
