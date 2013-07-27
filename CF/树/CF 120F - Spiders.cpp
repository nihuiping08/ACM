// 求树的直径
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
#define fir first
#define sec second

/******** program ********************/


const int MAXN = 5e2+5;
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
void dfs(int x,int f,int dep){
    if(dep>MAX){
        MAX = dep;
        now = x;
    }
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==f)continue;
        dfs(y,x,dep+1);
    }
}

int main(){

    bool ok = true;

#ifndef ONLINE_JUDGE
    ok = false;
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    if(ok){
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    }

    int ncase;
    while(cin>>ncase){
        int ans = 0;
        while(ncase--){
            int n;
            RD(n);
            memset(po,0,sizeof(po));
            tol = 0;
            int x,y;
            rep1(i,n-1){
                RD2(x,y);
                add(x,y);
                add(y,x);
            }
            MAX = 0;
            dfs(1,0,0);
            int tmp = now;
            MAX = 0;
            dfs(tmp,0,0);
            ans += MAX;
        }
        cout<<ans<<endl;
    }

	return 0;
}
