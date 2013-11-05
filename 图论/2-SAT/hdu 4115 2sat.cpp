/*

分析：由于在建模过程中会出现缺信息的情况，所以我们需要对于这种情况特殊处理，
增加x到x'的边

*/
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

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
#define lson rt<<1
#define rson rt<<1|1
#define SZ(x) x.size()

/******** program ********************/

const int MAXN = 20005;
const int MAXM = 500005;

int po[MAXN],tol;
int dfn[MAXN],fa[MAXN],low[MAXN],sta[MAXN],top,dep,bcnt;
bool use[MAXN];
int id[MAXN][4],a[MAXN];
int n,m;

struct node{
    int y,next;
}edge[MAXM];

void dfs(int x){
    dfn[x] = low[x] = ++ dep;
    sta[++top] = x;
    use[x] = true;
    int y;
    for(int i=po[x];i;i=edge[i].next){
        y = edge[i].y;
        if(!dfn[y]){
            dfs(y);
            cmin(low[x],low[y]);
        }else if(use[y])
            cmin(low[x],dfn[y]);
    }
    if(low[x]==dfn[x]){
        ++ bcnt;
        do{
            y = sta[top--];
            use[y] = false;
            fa[y] = bcnt;
        }while(x!=y);
    }
}

bool sat(){
    Clear(dfn);
    Clear(use);
    top = bcnt = dep = 0;
    int n2 = n*2;
    rep1(i,n2)
        if(!dfn[i])
            dfs(i);
    rep1(i,n)
        if(fa[i]==fa[i+n])
            return false;
    return true;
}

void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

int ssize = 128 << 20; // 256MB
char *ppp = (char*)malloc(ssize) + ssize;
__asm__("movl %0, %%esp\n" :: "r"(ppp) );

    int x,y,z,ncase, Ncase = 0;
    RD(ncase);
    while(ncase--){
        RD2(n,m);
        Clear(id);
        rep1(i,n){
            RD(x);
            a[i] = --x;
            id[i][x] = i;
            id[i][ (x+1)%3 ] = i+n;
        }
        Clear(po);
        tol = 0;
        bool ok = true;
        while(m--){
            RD3(x,y,z);

            rep(i,3){
                rep(j,3){
                    int px = id[x][i];
                    int py = id[y][j];
                    if(!px||!py||i!=j)
                        continue;

                    int nx,ny;
                    if(px>n)nx = px-n;
                    else nx = px+n;
                    if(py>n)ny = py-n;
                    else ny = py+n;

                    if(!z){
                        add(px,py);
                        add(py,px);
                        if(a[x]!=a[y]){
                            add(nx,px);
                            add(ny,py);
                        }
                    }else{
                        add(px,ny);
                        add(py,nx);
                    }
                }
            }
        }
        printf("Case #%d: %s\n",++Ncase,ok&&sat()?"yes":"no");
    }
    return 0;
}
