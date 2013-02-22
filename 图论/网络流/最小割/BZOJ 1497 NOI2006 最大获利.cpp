/*

把每个用户和每个站点都看成一个顶点。建立网络，从源点S向每个用户连接
一条容量为收益的有向边，每个用户向相关的两个站点连接一条容量为无穷大
的 有向边，每个站点向汇点T连接一条容量为成本的有向边。求出网络最小割
集的容量就是Maxflow=（未被选的用户的收益之和 + 被选择的站点的成本之
和）。设Total为所有用户的收益之和，我们要求的是（被选的用户的收益之
和 – 被选择的站点的成本之和），恰好等于Total – Maxflow，就是最大收益。

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 60005;
const int maxm = 1000020;
const int inf = 1e9;
#define debug puts("here");

struct node{
    int y,f,next;
}edge[maxm];

int arc[maxn],pre[maxn],dis[maxn],gap[maxn],cf[maxn];
int n,m,s,t,ans;
int po[maxn],tol;

void add(int x,int y,int f){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].next = po[x];
    po[x] = tol;

    edge[++tol].y = x;
    edge[tol].f = 0;
    edge[tol].next = po[y];
    po[y] = tol;
}

void sap(){
    memset(dis,0,sizeof(dis));
    memset(gap,0,sizeof(gap));
    gap[0] = n;
    for(int i=1;i<=n;i++)
        arc[i] = po[i];
    int i = s;
    int MIN;
    int aug = inf;
    int f = 0;
    bool ok;

    while(dis[s]<n){
        ok = false;
        cf[i] = aug;
        for(int j=arc[i];j;j=edge[j].next)
            if(edge[j].f>0&&dis[edge[j].y]+1==dis[i]){
                ok = true;
                aug = min(aug,edge[j].f);
                arc[i] = j;
                i = edge[j].y;
                pre[i] = j;
                if(i==t){
                    f += aug;
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
        MIN = n-1;
        for(int j=po[i];j;j=edge[j].next)
            if(edge[j].f>0&&dis[edge[j].y]<MIN){
                MIN = dis[edge[j].y];
                arc[i] = j;
            }
        if(--gap[dis[i]]==0)
            break;
        dis[i] = MIN+1;
        gap[dis[i]] ++;
        if(i!=s){
            i = edge[pre[i]^1].y;
            aug = cf[i];
        }
    }
    cout<<ans-f<<endl;
}

int main(){
    freopen("sum.in","r",stdin);
    int x,y,z;
    while(cin>>n>>m){
        memset(po,0,sizeof(po));
        tol = 1;
        s = n+m+1;
        t = s+1;
        ans = 0;

        for(int i=1;i<=n;i++){
            scanf("%d",&x);
            add(i,t,x);
            //ans += x;
        }
        for(int i=1+n;i<=n+m;i++){
            scanf("%d%d%d",&x,&y,&z);
            add(s,i,z);
            add(i,y,inf);
            add(i,x,inf);
            ans += z;
        }
        n = t;
        sap();
    }
    return 0;
}
