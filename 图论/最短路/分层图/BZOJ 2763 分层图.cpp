/*

可以选择k条路免费，问最小费用

分析：
简单分层图
增加一维，求最短路

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

const int MAXN = 100005;

int po[MAXN],tol;
int dis[MAXN][11];
bool use[MAXN];
int s,t;
int n,m,k;

struct node{
    int y,val,next;
}edge[MAXN];

void spfa(){
    memset(use,false,sizeof(use));
    memset(dis,0x3f,sizeof(dis));
    Clear(dis[s]);

    queue<int> q;
    q.push(s);

    while(!q.empty()){
        int x = q.front();
        q.pop();
        use[x] = false;

        for(int i=po[x];i;i=edge[i].next){
            for(int j=0;j<=k;j++){
                int y = edge[i].y;

                if(dis[y][j]>edge[i].val+dis[x][j]){
                    dis[y][j] = edge[i].val+dis[x][j];
                    if(!use[y]){
                        use[y] = true;
                        q.push(y);
                    }
                }

                if(j&&dis[y][j]>dis[x][j-1]){
                    dis[y][j] = dis[x][j-1];
                    if(!use[y]){
                        use[y] = true;
                        q.push(y);
                    }
                }
            }
        }
    }

    int ans = dis[0][0];
    rep(i,k+1)
        cmin(ans,dis[t][i]);
    cout<<ans<<endl;
}

void add(int x,int y,int z){
    edge[++tol].y = y;
    edge[tol].val = z;
    edge[tol].next = po[x];
    po[x] = tol;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m>>k){
        RD2(s,t);
        s ++;
        t ++;

        int x,y,z;

        memset(po,0,sizeof(po));
        tol = 0;
        rep1(i,m){
            RD3(x,y,z);
            x ++;
            y ++;
            add(x,y,z);
            add(y,x,z);
        }

        spfa();
    }

	return 0;
}
