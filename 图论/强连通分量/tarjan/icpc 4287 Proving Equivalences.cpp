/*

第七题 题目：icpc 4287 Proving Equivalences
    a能够推出b，b能够推出c，现在问增加多少个关系，使得所有的关系相互等价

分析：不难想到构造出有向图，然后求出图中的强连通分量，缩点之后求max(id,od)。
id表示所有入度为0的顶点个数，od表示出度为0的个数，但是得要注意的是当连通块
只有一个的时候，答案应该是0（缩点里的所有元素相互等价）

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn =  50005;
const int maxm =  100005;

int po[maxn],tol;
int stack[maxn],dfn[maxn],low[maxn],father[maxn],bcnt,depth,top;
bool instack[maxn];
int id[maxn],od[maxn];
int n,m;

struct node{
    int y,next;
}edge[maxm];

void dfs(int x){	//递归实现tarjan算法
    low[x] = dfn[x] = ++depth;
    instack[x] = true;
    stack[++top] = x;
    int y;
    for(int i=po[x];i;i=edge[i].next){
        y = edge[i].y;
        if(!dfn[y]){
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
    memset(instack,false,sizeof(instack));
    memset(dfn,0,sizeof(dfn));
    top = bcnt = depth = 0;
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            dfs(i);
    if(bcnt==1){
        puts("0");
        return;
    }

    memset(id,0,sizeof(id));
    memset(od,0,sizeof(od));
    for(int x=1;x<=n;x++)
        for(int j=po[x];j;j=edge[j].next){
            int y = edge[j].y;
            if(father[x]!=father[y]){
                od[father[x]] ++;
                id[father[y]] ++;
            }
        }
    int id_cnt = 0,od_cnt = 0;
    for(int i=1;i<=bcnt;i++){
        if(!id[i])
            id_cnt ++;
        if(!od[i])
            od_cnt ++;
    }
    cout<<max(id_cnt,od_cnt)<<endl;
}

void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

int main(){
    freopen("sum.in","r",stdin);
    int ncase;
    cin>>ncase;
    while(ncase--){
        memset(po,0,sizeof(po));
        tol = 0;
        int x,y;
        cin>>n>>m;
        while(m--){
            scanf("%d%d",&x,&y);
            add(x,y);
        }
        tarjan();
    }
    return 0;
}
