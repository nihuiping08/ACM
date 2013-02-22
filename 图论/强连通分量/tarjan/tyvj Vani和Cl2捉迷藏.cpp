#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 3005;
const int maxm = 30005;
#define debug puts("here");

struct node{
    int y,next;
}edge[maxm];

int po[maxn],tol;
int n,m;
int father[maxn],stack[maxn],dfn[maxn],low[maxn];
int bcnt,top,depth;
bool instack[maxn];
int id[maxn];

void dfs(int x){
    instack[x] = true;
    stack[++top] = x;
    low[x] = dfn[x] = ++depth;
    int y;
    for(int i=po[x];i;i=edge[i].next){
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
    bcnt = depth = top = 0;
    int ans = 0;

    for(int i=1;i<=n;i++)
        if(!low[i])
            dfs(i);
    memset(id,0,sizeof(id));
    for(int i=1;i<=n;i++)
        for(int j=po[i];j;j=edge[j].next){
            int y = edge[j].y;
            if(father[i]!=father[y]){
                id[father[y]]++;
            }
        }
    for(int i=1;i<=n;i++)
        if(id[father[i]]==0)
            ans++;
    cout<<ans<<endl;
}

void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m){
        int x,y;
        tol = 0;
        memset(po,0,sizeof(po));
        while(m--){
            scanf("%d%d",&x,&y);
            add(x,y);
        }
        tarjan();
    }
    return 0;
}
