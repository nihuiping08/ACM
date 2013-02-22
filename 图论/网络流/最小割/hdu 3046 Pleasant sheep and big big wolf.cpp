/*

最小割：对于每个相邻格子建立流量为1的无向边
        把狼连上汇点，把羊连上源点，流量都是1

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 205;
const int maxn = 40005;
const int maxm = 400005;
const int inf = 1e9;

int n,m,s,t;
int po[maxn],tol;
int arc[maxn],pre[maxn],cf[maxn],dis[maxn],gap[maxn];
int map[X][X];

struct node{
    int y,f,next;
}edge[maxm];

void add(int x,int y,int f){
    edge[++tol].f = f;
    edge[tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;

    edge[++tol].f = 0;
    edge[tol].y = x;
    edge[tol].next = po[y];
    po[y] = tol;
}

int sap(){
    memset(gap,false,sizeof(gap));
    memset(dis,0,sizeof(dis));
    gap[0] = t;
    for(int i=1;i<=t;i++)
        arc[i] = po[i];
    int i = s;
    int MIN;
    int aug = inf;
    int ans = 0;
    bool ok;

    while(dis[s]<t){
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
                    ans += aug;
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
        MIN = t-1;
        for(int j=po[i];j;j=edge[j].next)
            if(edge[j].f>0&&dis[edge[j].y]<MIN){
                MIN = dis[edge[j].y];
                arc[i] = j;
            }
        if(--gap[dis[i]]==0)
            break;
        dis[i] = MIN+1;
        gap[dis[i]]++;
        if(i!=s){
            i = edge[pre[i]^1].y;
            aug = cf[i];
        }
    }
    return ans;
}

void build(){
    memset(po,0,sizeof(po));
    tol = 1;
    s = n*m+1;
    t = s+1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&map[i][j]);
            if(i)
                add(i*m+j,i*m+j-m,1);
            if(j)
                add(i*m+j,i*m+j-1,1);
            if(i<n-1)
                add(i*m+j,i*m+j+m,1);
            if(j<m-1)
                add(i*m+j,i*m+j+1,1);
            if(map[i][j]==1)
                add(s,i*m+j,inf);
            else if(map[i][j])
                add(i*m+j,t,inf);
        }
    }
    n = t;
}

int main(){
    freopen("sum.in","r",stdin);
    int ncase = 0;
    while(cin>>n>>m){
        build();
        printf("Case %d:\n",++ncase);
        cout<<sap()<<endl;
    }
    return 0;
}
