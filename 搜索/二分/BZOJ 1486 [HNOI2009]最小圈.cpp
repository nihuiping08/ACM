/*

题目：寻找环的最小平均值
分析：二分+dfs迅爪负环

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

/******** program ********************/

const int MAXN = 3005;
const int MAXM = 2e4+5;
const double esp = 1e-8;

int po[MAXN],tol,n,m;
double dis[MAXN];
bool use[MAXN];

struct node{
    int y,next;
    double w;
}edge[MAXM];

bool dfs(int x){
    use[x] = true;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        double d = edge[i].w+dis[x];
        if(d<dis[y]){
            if(use[y]){
                use[x] = false;
                return true;
            }else{
                dis[y] = d;
                if(dfs(y)){
                    use[y] = false;
                    return true;
                }
            }
        }
    }
    use[x] = false;
    return false;
}

bool check(){
    rep1(i,n)
        dis[i] = 0;
    rep1(i,n)
        if(dfs(i))
            return true;
    return false;
}

void add(int x,int y,double z){
    edge[++tol].y = y;
    edge[tol].w = z;
    edge[tol].next = po[x];
    po[x] = tol;
}

void change(double mid){
    rep1(i,tol)
        edge[i].w -= mid;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m){
        memset(po,0,sizeof(po));
        tol = 0;
        int x,y;
        double z;
        while(m--){
            scanf("%d%d%lf",&x,&y,&z);
            add(x,y,z);
        }
        double l = -1e7;
        double r = 1e7;
        rep(i,100){
            double mid = (l+r)/2;
            change(mid);
            if(check())
                r = mid;
            else
                l = mid;
            change(-mid);
        }
        printf("%.8lf\n",r);
    }

    return 0;
}
