/*

题目：
    A,B两个国家正在交战，其中A国的物资运输网中有N个中转站，
    M条单向道路。设其中第i (1≤i≤M)条道路连接了vi,ui两个中转站，
    那么中转站vi可以通过该道路到达ui中转站，如果切断这条道路，
    需要代价ci。现在B国想找出一个路径切断方案，使中转站s不能到
    达中转站t，并且切断路径的代价之和最小。 小可可一眼就看出，
    这是一个求最小割的问题。但爱思考的小可可并不局限于此。现在
    他对每条单向道路提出两个问题： 问题一：是否存在一个最小代
    价路径切断方案，其中该道路被切断？ 问题二：是否对任何一个
    最小代价路径切断方案，都有该道路被切断？ 现在请你回答这两
    个问题。

分析：
    先用最大流求出残余网络，然后再用tarjan求出残余网络的强连通
    分量，若边的两个顶点不在同一个强连通分量上且他的正向流量可
    以为0，所以问题一为1。若在此基础上一个顶点与源点在同一个强
    连通分量上，且另一个顶点与汇点在同一个强连通分量上，则问题
    二为1

    判断边是否在某个最小割集中 以及 判断边是否为最小割的必需边。
    在残余网络中求出强连通分量，对于不在同一强连通分量且满流的
    边，必然在某一最小割中。

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 4005;
const int maxm = 120005;
const int inf = 1e9;

int po[maxn],tol;
int dis[maxn],pre[maxn],cf[maxn],arc[maxn],gap[maxn];
int n,m,s,t;
int stack[maxn],father[maxn],low[maxn],dfn[maxn];
int bcnt,top,depth;
bool instack[maxn];

struct node{
    int y,f,next;
}edge[maxm];

void dfs(int x){
    dfn[x] = low[x] = ++depth;
    stack[++top] = x;
    instack[x] = true;
    int y;
    for(int i=po[x];i;i=edge[i].next){
        if(edge[i].f<=0)
            continue;
        y = edge[i].y;
        if(!low[y]){
            dfs(y);
            low[x] = min(low[x],low[y]);
        }
        else if(instack[y])
            low[x] = min(low[x],dfn[y]);
    }
    if(low[x]==dfn[x]){
        ++bcnt;
        do{
            y = stack[top--];
            instack[y] = false;
            father[y] = bcnt;
        }while(x!=y);
    }
}

void tarjan(){
    memset(low,0,sizeof(low));
    memset(instack,false,sizeof(instack));
    top = depth = bcnt = 0;
    for(int i=1;i<=n;i++)
        if(!low[i])
            dfs(i);
}

void sap(){
    memset(dis,0,sizeof(dis));
    memset(gap,0,sizeof(gap));
    gap[0] = n;
    for(int i=0;i<=n;i++)
        arc[i] = po[i];
    int i = s;
    int aug = inf;
    bool ok = false;

    while(dis[s]<n){
        cf[i] = aug;
        ok = false;
        for(int j=arc[i];j;j=edge[j].next)
            if(edge[j].f>0&&dis[edge[j].y]+1==dis[i]){
                ok = true;
                aug = min(aug,edge[j].f);
                i = edge[j].y;
                pre[i] = j;
                if(i==t){
                    while(i!=s){
                        edge[pre[i]].f -= aug;
                        edge[pre[i]^1].f += aug;
                        i = edge[pre[i]^1].y;
                    }
                    aug = inf;
                }
                break;
            }
        if(ok)
            continue;
        int MIN = inf;
        for(int j=po[i];j;j=edge[j].next)
            if(edge[j].f>0&&dis[edge[j].y]<MIN){
                MIN = dis[edge[j].y];
                arc[i] = j;
            }
        if(--gap[dis[i]]==0)
            break;
        dis[i] = MIN+1;
        ++gap[dis[i]];
        if(i!=s){
            i = edge[pre[i]^1].y;
            aug = cf[i];
        }
    }
}

void add(int x,int y,int f){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].next = po[x];
    po[x] = tol;
}

void solve(){
    for(int i=1;i<=m;i++){
        int y = edge[i<<1].y;
        int x = edge[i<<1|1].y;
        int a = 0;
        int b = 0;
        if(father[x]!=father[y]&&!edge[i<<1].f){
            a = 1;
            if(father[x]==father[s]&&father[y]==father[t])
                b = 1;
        }
        printf("%d %d\n",a,b);
    }
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m>>s>>t){
        memset(po,0,sizeof(po));
        tol = 1;
        int x,y,z;
        for(int i=0;i<m;i++){
            scanf("%d%d%d",&x,&y,&z);
            add(x,y,z);
            add(y,x,0);
        }
        sap();
        tarjan();
        solve();
    }
    return 0;
}
