/*

题目：输出从1到n的最短路的路径
分析:spfa记录路径即可

*/
#include <set>
#include <map>
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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 1e5+5;

ll dis[MAXN];
int pre[MAXN];
bool use[MAXN];
int po[MAXN],tol;
int q[MAXN],head,tail;
int n,m;

struct node{
    int y,next;
    ll dis;
}edge[MAXN*3];

void dfs(int x){
    if(x){
        dfs(pre[x]);
        printf("%d ",x);
    }
}

void add(int x,int y,int d){
    edge[++tol].dis = d;
    edge[tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

void spfa(){
    memset(use,0,sizeof(use));
    for(int i=0;i<=n;i++)
        dis[i] = ll(100000000)*10000000;

    q[tail++] = 1;
    dis[1] = 0;
    pre[1] = 0;

    while(head<tail){
        int x = q[head++];
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            int y = edge[i].y;
            ll tmp = dis[x]+edge[i].dis;
            if(dis[y]>tmp){
                dis[y] = tmp;
                pre[y] = x;
                if(!use[y]){
                    use[y] = true;
                    q[tail++] = y;
                }
            }
        }
    }
    if(dis[n]==dis[0]){
        puts("-1");
        return;
    }
    dfs(pre[n]);
    printf("%d",n);
    puts("");
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int x,y,d;
    RD2(n,m);
    while(m--){
        RD3(x,y,d);
        add(x,y,d);
        add(y,x,d);
    }
    spfa();

	return 0;
}
