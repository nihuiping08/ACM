/*

题目：寻找第k短路

分析：A*算法。
	A*算法其实就是一个寻路时使用估价函数，智能化的认为某条路更优就往该路走的一种策略。
	公式表示为： f(n)=g(n)+h(n),
	其中 f(n) 是从初始点经由节点n到目标点的估价函数，
	g(n) 是在状态空间中从初始节点到n节点的实际代价，
	h(n) 是从n到目标节点最佳路径的估计代价。
	保证找到最短路径（最优解的）条件，关键在于估价函数h(n)的选取：
	估价值h(n)<= n到目标节点的距离实际值，这种情况下，搜索的点数多，搜索范围大，效率低。
	但能得到最优解。
	如果 估价值>实际值,搜索的点数少，搜索范围小，效率高，但不能保证得到最优解。

这题：
	建立反向图，然后跑一次最短路，h函数即为节点x到t点的距离。g函数就是g+w。
	使用计数器，当t的计数器到达k次时，即为答案
	
	
*/
#include <set>
#include <map>
#include <list>
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
#define PQ priority_queue
#define cmax(x,y) x = max(x,y)
#define cmin(x,y) x = min(x,y)
#define Clear(x) memset(x,0,sizeof(x))
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/

const int MAXN = 1e3+5;
const int INF = 1e9;

vector< PII > adj[MAXN];
vector< PII > radj[MAXN];
int dis[MAXN];
bool use[MAXN];
int id[MAXN];
int n,m;

struct node{
    int x,g,h;
    node(){}
    node(int a,int b,int c){
        x = a;
        g = b;
        h = c;
    }
    friend bool operator < (node a,node b){
        return a.g+a.h>b.g+b.h;
    }
};

void spfa(int s){
    queue<int> q;
    q.push(s);
    rep1(i,n)
        dis[i] = INF;
    dis[s] = 0;
    memset(use,false,sizeof(use));
    while(q.size()){
        int x = q.front();
        q.pop();
        use[x] = false;
        foreach(i,radj[x]){
            int y = radj[x][i].first;
            int t = radj[x][i].second + dis[x];
            if(dis[y]>t){
                dis[y] = t;
                if(!use[y]){
                    use[y] = true;
                    q.push(y);
                }
            }
        }
    }
}

int Astar(int s,int t,int k){
    if(dis[s]==INF)return -1;
    if(s==t)k ++;

    Clear(id);

    priority_queue< node > q;
    q.push( node( s,0,dis[s] ) );

    while(q.size()){
        node p = q.top();
        q.pop();
        int x = p.x;

        id[x] ++;
        if(id[x]>k)continue;
        if(id[t]==k)return p.g+p.h;

        foreach(i,adj[x]){
            int y = adj[x][i].first;
            int w = adj[x][i].second;
            q.push( node( y,p.g+w,dis[y] ) );
        }
    }

    return -1;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m){
        rep1(i,n){
            adj[i].clear();
            radj[i].clear();
        }
        int x,y,z;
        while(m--){
            RD3(x,y,z);
            adj[x].pb( MP(y,z) );
            radj[y].pb( MP(x,z) );
        }

        int s,t,k;
        RD3(s,t,k);
        spfa(t);
        cout<<Astar(s,t,k)<<endl;
    }

	return 0;
}
