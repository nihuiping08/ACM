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

char IN;
bool NEG;
inline void Int(int &x){
    NEG = 0;
    while(!isdigit(IN=getchar()))
        if(IN=='-')NEG = 1;
    x = IN-'0';
    while(isdigit(IN=getchar()))
        x = x*10+IN-'0';
    if(NEG)x = -x;
}
inline void LL(ll &x){
    NEG = 0;
    while(!isdigit(IN=getchar()))
        if(IN=='-')NEG = 1;
    x = IN-'0';
    while(isdigit(IN=getchar()))
        x = x*10+IN-'0';
    if(NEG)x = -x;
}

/******** program ********************/

const int MAXN = 105;
const double INF = 1e50;

int pre[MAXN],id[MAXN],use[MAXN];
int px[MAXN],py[MAXN];
double in[MAXN];

struct Edge{
    int x,y;
    double cost;
    Edge(){}
    Edge(int _x,int _y,double _cost):x(_x),y(_y),cost(_cost){}
}g[MAXN*MAXN];
double treeDiagrm(int root,int n,int m){
    double ans = 0;
    while(true){
        rep1(i,n)
            in[i] = INF;

        rep1(i,m){
            int x = g[i].x , y = g[i].y;
            double cost = g[i].cost;
            if(cost<in[y]&&y!=x)
                pre[y] = x , in[y] = cost;
        }
        in[root] = 0 , pre[root] = root;
        rep1(x,n){
            if(in[x]>1e20)return -1;
            ans += in[x];
        }
        Clear(use);
        Clear(id);
        int tot = 0;
        rep1(i,n){
            if(use[i])continue;
            int x = i;
            while(!use[x])use[x] = i , x = pre[x];
            if(use[x]!=i||x==root)continue;
            id[x] = ++ tot;
            for(int t=pre[x];t!=x;t=pre[t])
                id[t] = tot;
        }
        if(!tot)break;
        rep1(i,n)if(!id[i])id[i] = ++ tot;

        rep1(i,m){
            g[i].cost -= in[g[i].y];
            g[i].x = id[g[i].x];
            g[i].y = id[g[i].y];
        }
        n = tot;
        root = id[root];
    }
    return ans;
}

double cal(int x,int y){
    return sqrt(0.0+x*x+y*y);
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int x,y,n,m;
    while(~RD2(n,m)){
        rep1(i,n)
            RD2(px[i],py[i]);
        rep1(i,m){
            RD2(x,y);
            g[i] = Edge(x,y,cal(px[x]-px[y],py[x]-py[y]));
        }
        double ans = treeDiagrm(1,n,m);
        if(ans>0)
            printf("%.2lf\n",ans);
        else puts("poor snoopy");
    }

    return 0;
}
