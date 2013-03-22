/*

题目：
    给出m条无向边a,b,c，找最大流，输出给出的边的方向。
    提示：给出的点的入边权等于出的边权，且该边权为最大流的边权。

分析：
    最大流加dfs输出路径会TLE。
    注意到那个提示，我们可以直接从源点开始BFS，由于出边权等于入边权，且出边
    只有一条。所以我们在BFS过程中，只需要把出边的另一个顶点放进队列，然后BFS
    一次就行了

*/
#include <queue>
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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

const int MAXN = 2e5+5;

int po[MAXN],tol;
int sum[MAXN];
int ans[MAXN];
int n,m;

struct node{
    int x,y,id,cost,next;
    bool ok;
}edge[MAXN*2];

void add(int x,int y,int cost,int id,bool ok){
    edge[++tol].x = x;
    edge[tol].y = y;
    edge[tol].cost = cost;
    edge[tol].ok = ok;
    edge[tol].id = id;
    edge[tol].next = po[x];
    po[x] = tol;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif
    //ios::sync_with_stdio(0);

    int x,y,z;
    bool ok = false;
    while(~RD2(n,m)){
        ok?puts(""):ok = true;
        memset(sum,0,sizeof(sum));
        memset(po,0,sizeof(po));
        tol = 1;
        rep1(i,m){
            cin>>x>>y>>z;
            add(x,y,z,i,0);
            add(y,x,z,i,1);
            sum[x] += z;
            sum[y] += z;
        }
        rep1(i,n)
            sum[i] >>= 1;

        memset(ans,-1,sizeof(ans));
        queue<int> q;
        q.push(1);

        while(q.size()){
            int x = q.front();
            q.pop();
            for(int i=po[x];i;i=edge[i].next){
                int y = edge[i].y;
                int id = edge[i].id;
                if(ans[id]!=-1)
                    continue;
                ans[id] = edge[i].ok;
                sum[y] -= edge[i].cost;
                if(y!=n&&sum[y]==0)
                    q.push(y);
            }
        }
        rep1(i,m)
            cout<<ans[i]<<endl;
    }

	return 0;
}
