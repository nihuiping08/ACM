/*

题目：从树中删除任意一条边，使得该边的边权乘以两个连通块的最大直径的值最小
分析：先求出直径，如果删除的边在直径上，则从直径的两边各搜一次，记录每个直径节点能够到达的最大值
以及次大值。最后再搜一次得到答案

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

/******** program ********************/

const int MAXN = 1000005;

int po[MAXN],tol;
ll dpfir[MAXN],dpsec[MAXN],dis[MAXN][3];
bool is[MAXN];
int n;

struct node{
    int y,val,id,next;
}edge[MAXN*2];

void add(int x,int y,int val,int id){
    edge[++tol].y = y;
    edge[tol].val = val;
    edge[tol].id = id;
    edge[tol].next = po[x];
    po[x] = tol;
}

int MAX,ans_x;
void dfsR(int x,int fa,int dep){
    if(dep>MAX){
        MAX = dep;
        ans_x = x;
    }
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)continue;
        dfsR(y,x,dep+1);
    }
}

bool dfsPath(int x,int fa,int end){
    if(x==end)return true;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)continue;
        if( dfsPath(y,x,end) ){
            is[ edge[i].id ] = true;
            return true;
        }
    }
    return false;
}

void dfsAns(int x,int fa,int id){
    dpfir[x] = dpsec[x] = dis[x][id] = 0;
    int fir = 0 , sec = 0;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)continue;
        dfsAns(y,x,id);
        int tmp = dpfir[y]+1;
        if( tmp>fir ){
            sec = fir;
            fir = tmp;
        }else if(tmp>sec)
            sec = tmp;
        cmax( dis[x][id] , dis[y][id] );
    }
    dpfir[x] = fir;
    dpsec[x] = sec;
    cmax( dis[x][id],ll(fir)+sec );
}

int pos;
ll ans;
void dfs(int x,int fa){
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa) continue;
        dfs(y,x);
        if(is[ edge[i].id ]){
            ll tmp = max( dis[x][1],dis[y][0] )*edge[i].val;
            if(tmp<ans){
                ans = tmp;
                pos = edge[i].id;
            }else if(tmp==ans)
                cmin(pos,edge[i].id);
        }else{
            ll tmp = (ll)MAX*edge[i].val;
            if(tmp<ans){
                ans = tmp;
                pos = edge[i].id;
            }else if(tmp==ans)
                cmin(pos,edge[i].id);
        }
    }
}

int main(){

#pragma comment(linker, "/STACK:1024000000,1024000000")

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int x,y,val,ncase;
    RD(ncase);
    rep1(Ncase,ncase){
        memset(po,0,sizeof(po));
        tol = 0;
        RD(n);
        for(int i=1;i<n;i++){
            RD3(x,y,val);
            add(x,y,val,i);
            add(y,x,val,i);
        }

        MAX = 0;
        dfsR(1,0,0);
        int x = ans_x;
        MAX = 0;
        dfsR(x,0,0);
        int y = ans_x;
        //cout<<"R  "<<x<<" "<<y<<" "<<MAX<<endl;

        Clear(is);
        dfsPath(x,0,y);

        dfsAns(x,0,0);
        dfsAns(y,0,1);

        ans = 10000000000000LL;
        dfs(x,0);
        //cout<<"dsa =   "<<ans<<endl;

        printf("Case #%d: ",Ncase);
        cout<<pos<<endl;
    }

	return 0;
}
