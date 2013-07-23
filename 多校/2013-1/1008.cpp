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

/******** program ********************/

const int MAXN = 2e5+5;
const int INF = 1e9;

int po[MAXN],tol;

struct node{
    int y,next;
}edge[MAXN];

void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

int MAX,now;
void dfs_1(int x,int f,int dep){
    if(dep>MAX){
        MAX = dep;
        now = x;
    }
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==f)continue;
        dfs_1(y,x,dep+1);
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    while(ncase--){
        int x,y;
        int n,m;
        RD2(n,m);
        memset(po,0,sizeof(po));
        tol = 0;
        REP(i,2,n){
            RD2(x,y);
            add(x,y);
            add(y,x);
        }

        now = MAX = 0;
        dfs_1(1,0,1);

        int tmp = now;
        //cout<<"dsa "<<tmp<<endl;

        now = MAX = 0;
        dfs_1(tmp,0,1);
        //cout<<"r =  "<<now<<" "<<MAX<<endl;

        while(m--){
            RD(x);
            if(x>MAX)
                printf("%d\n",(x-MAX)*2+MAX-1);
            else
                printf("%d\n",x-1);
        }
    }

	return 0;
}
