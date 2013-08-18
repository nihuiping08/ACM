/*

题目：构造以1节点为根的一棵树，是的费用最少，
	树的费用 = sigma( 以该树边的一个节点为根的子树的所有节点的权值和*边权 )
	
分析：很容易看出来，其实就是从根1出发，到每个节点的最短路*该节点的权值

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

const int MAXN = 50005;
const ll INF = 1e18;

int po[MAXN],tol;
int val[MAXN];
ll dis[MAXN];
bool use[MAXN];
int n,m;

struct node{
    int y,val,next;
}edge[MAXN*2];

ll spfa(){
    Clear(use);
    rep1(i,n)
        dis[i] = INF;
    dis[1] = 0;
    queue<int> q;
    q.push(1);
    while(!q.empty()){
        int x = q.front();
        q.pop();
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            int y = edge[i].y;
            ll v = edge[i].val+dis[x];
            if(dis[y]>v){
                dis[y] = v;
                if(!use[y]){
                    use[y] = true;
                    q.push(y);
                }
            }
        }
    }

    ll ans = 0;
    rep1(i,n)
        cmax(ans,dis[i]);
    if(ans==INF)return -1;
    ans = 0;
    rep1(i,n)
        ans += dis[i]*val[i];
    return ans;
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

    int ncase;
    RD(ncase);
    while(ncase--){
        int x,y,z;
        RD2(n,m);
        rep1(i,n)
            RD(val[i]);
        Clear(po);
        tol = 0;

        while(m--){
            RD3(x,y,z);
            add(x,y,z);
            add(y,x,z);
        }
        if(n==0||n==1){
            puts("0");
            continue;
        }

        ll ans = spfa();
        if(ans==-1)
            puts("No Answer");
        else
            cout<<ans<<endl;
    }

	return 0;
}
