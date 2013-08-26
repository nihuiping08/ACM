/*

题目：给出一棵树，问与节点v的第k个祖先相同的节点数有多少个。

分析：

　　寻找节点v的第k个祖先，这不就是qtree2简化版吗，但是怎么统计该祖先拥有多少个深度为k的儿子？

　　我们可以对于深度为d的所有节点放到一个数组中，这时需要知道的是深度为d的数组中某个连续区间都属于该子树的长度。

　　某棵子树的信息？这时可以考虑一下dfs序列。。。

　　dfs序列把整棵子树放在同一个区间，不懂dfs序的可以做做这两题：

　　BZOJ 1103 [POI2007]大都市meg，BZOJ 1782 [Usaco2010 Feb]slowdown 慢慢游。

　　

　　于是，我们dfs时把节点x的进入时的时间戳放到深度为d的数组中，二分出询问节点v进入、出去
	时的时间戳所在的位置，算出该区间长度即可。

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
/*

#pragma comment(linker, "/STACK:1024000000,1024000000")

int size = 256 << 20; // 256MB
char *p = (char*)malloc(size) + size;
__asm__("movl %0, %%esp\n" :: "r"(p) );

*/

/******** program ********************/

const int MAXN = 1e5+5;
const int LOG = 18;

vector<int> adj[MAXN];

int a[MAXN];
int dep[MAXN];
int p[MAXN][LOG+1];
int st[MAXN],ed[MAXN],tim;
vector< int > vec[MAXN];

void dfs(int x,int fa,int depth){
    st[x] = tim++;
    dep[x] = depth;
    vec[depth].pb( tim );

    p[x][0] = fa;
    rep1(i,LOG)
        p[x][i] = p[ p[x][i-1] ][i-1];

    foreach(i,adj[x])
        dfs(adj[x][i],x,depth+1);

    ed[x] = tim++;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int n;
    int ncase = 0;
    while(cin>>n){
        ncase?puts("------------------------"):ncase = 1;
        rep1(i,n){
            adj[i].clear();
            vec[i].clear();
        }
        int tot = 0;
        rep1(i,n){
            RD(a[i]);
            tot += !a[i];
            adj[ a[i] ].pb(i);
        }

        tim = 0;
        dfs(0,0,0);

        int m,x,k;
        RD(m);
        while(m--){
            RD2(x,k);
            int d = dep[x];

            rep(i,LOG)
                if( k>>i & 1 )
                    x = p[x][i];
            if(!x){
                printf("0 ");
                continue;
            }
            int ans = lower_bound(All(vec[d]),ed[x])-lower_bound(All(vec[d]),st[x]-1)-1;
            printf("%d ",ans);
        }
        cout<<endl;
    }

    return 0;
}
