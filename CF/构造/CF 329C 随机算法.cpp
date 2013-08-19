/*

题目：给出一个图，图的特点是：每个点最多只有两条边。现在需要重建图，使得新图中满足每个点最
多只有两条边，并且旧图中存在的边在新图中不会出现。

分析：随机算法，用random_suffle函数随机出一个排列，然后判断相邻的是否满足即可

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

int adj[MAXN][2];
int vec[MAXN][2];
int p[MAXN];
int ym[MAXN];

void add(int x,int y){
    if(adj[x][0])
        adj[x][1] = y;
    else
        adj[x][0] = y;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,m,x,y;
    while(cin>>n>>m){
        Clear(adj);
        rep(i,m){
            RD2(x,y);
            add(x,y);
            add(y,x);
        }

        rep1(i,n)
            p[i] = i;

        bool ans = false;
        rep(step,50){
            random_shuffle(p+1,p+n+1);
            bool ok = true;
            p[n+1] = p[1];
            for(int i=1;i<=m;i++){
                int x = p[i];
                int y = p[i+1];
                if( adj[x][0]==y || adj[x][1]==y )
                    ok = false;
                vec[i][0] = x;
                vec[i][1] = y;
            }
            if(ok){
                ans = true;
                rep1(i,m)
                    printf("%d %d\n",vec[i][0],vec[i][1]);
                break;
            }
        }
        if(!ans)
            puts("-1");
    }

	return 0;
}
