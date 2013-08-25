/*

题目：把无向图指定边的方向，使得原图变成有向图，问能否任意两点之间互达

分析：显然如果没有桥的话，存在满足题意的方案。
	输出答案时任意从一个点出发遍历一遍即可。

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

const int MAXN = 1e6+5;

int dfn[MAXN],low[MAXN],dep;
int po[MAXN],tol;
int n,m;

struct node{
    int x,y,id,next;
}edge[MAXN*2];

bool dfs(int x,int fa){
    low[x] = dfn[x] = ++ dep;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)continue;
        if(!dfn[y]){
            if(!dfs(y,x))
                return false;
            cmin( low[x],low[y] );

            if(low[y]>dfn[x])
                return false;
        }else
            cmin( low[x],dfn[y] );
    }
    return true;
}

void out(int x,int fa){
    low[x] = 1;
    for(int i=po[x];i;i=edge[i].next){
        int y = edge[i].y;
        if(y==fa)continue;
        //cout<<"dsa "<<x<<" "<<y<<endl;
        if( abs(edge[i].id)==1){
            edge[i].id = 2;
            edge[i^1].id = -2;
        }
        if(!low[y])
            out(y,x);
    }
}

void add(int x,int y,int id){
    edge[++tol].y = y;
    edge[tol].x = x;
    edge[tol].id = id;
    edge[tol].next = po[x];
    po[x] = tol;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m){
        Clear(po);
        tol = 1;

        int x,y;
        rep1(i,m){
            RD2(x,y);
            add(x,y,1);
            add(y,x,-1);
        }

        Clear(dfn);
        dep = 0;
        bool ok = true;
        rep1(x,n)
            if(!dfn[x]){
                if(!dfs(x,0)){
                    ok = false;
                    break;
                }
            }


        if(ok){
            Clear(low);
            out(1,0);
            for(int i=2;i<=tol;i++)
                if(edge[i].id>0)
                    printf("%d %d\n",edge[i].x,edge[i].y);
        }
        else
            puts("0");
    }

    return 0;
}

