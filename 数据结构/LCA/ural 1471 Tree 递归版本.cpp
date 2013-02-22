/*

µÝ¹é°æ±¾¡£¡£¡£
±¬Õ»==¡£

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxm = 200005;
const int maxn = 200005;
#define debug puts("here");

int n,m;
int po[maxn],tol,rp[maxm];
int p[maxn];
int ans[maxm],dis[maxn];
bool use[maxm];

struct node{
    int y,w,next;
}a[maxn],b[maxm];

void add(int x,int y,int w){
    a[++tol].y = y;
    a[tol].w = w;
    a[tol].next = po[x];
    po[x] = tol;
}

void radd(int x,int y,int id){
    b[++tol].y = y;
    b[tol].next = rp[x];
    b[tol].w = id;
    rp[x] = tol;
}

int find_set(int x){
    if(x!=p[x])
        p[x] = find_set(p[x]);
    return p[x];
}

void union_set(int x,int y){
    x = find_set(x);
    y = find_set(y);
    if(x!=y)
        p[y] = x;
}

void lca(int x,int w){
    dis[x] = w;
    p[x] = x;
    use[x] = true;
    int y,id;

    for(int i=rp[x];i;i=b[i].next){
        y = b[i].y;
        id = b[i].w;
        if(use[y])
            ans[id] = dis[x]+dis[y]-2*dis[find_set(y)];
    }

    for(int i=po[x];i;i=a[i].next){
        y = a[i].y;
        if(use[y])
            continue;
        lca(y,w+a[i].w);
        union_set(x,y);
    }
}

int main(){
    freopen("sum.in","r",stdin);
    int x,y,z;
    while(cin>>n){
        tol = 0;
        memset(po,0,sizeof(po));
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&x,&y,&z);
            x++;
            y++;
            add(x,y,z);
            add(y,x,z);
        }
        cin>>m;
        tol = 0;
        memset(rp,0,sizeof(rp));
        for(int i=1;i<=m;i++){
            scanf("%d%d",&x,&y);
            x++;
            y++;
            radd(x,y,i);
            radd(y,x,i);
        }
        memset(use,false,sizeof(use));
        lca(1,0);
        for(int i=1;i<=m;i++)
            printf("%d\n",ans[i]);
        /*for(int i=1;i<=n;i++)
            cout<<i<<"  "<<dis[i]<<endl;*/
    }
    return 0;
}
