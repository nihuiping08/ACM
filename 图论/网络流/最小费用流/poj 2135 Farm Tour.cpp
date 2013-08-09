/*

题目：
    给出边以及边权，现在问如何选择两条路径（没有相同的边）使得路径
    总边权最小

分析：
    建图的时候只需要对输入建立无向图就行了（费用为1），另外建立超
    级汇点以及超级源点，分别连上n,1两个点，费用为2
*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int maxn = 40005;
const int maxm = 40005;
const int inf = 2147483647;
#define debug puts("hers");

struct node{
    int y,f,c,next;
}edge[maxm];

int pre[maxn],dis[maxn],po[maxn],tol;
int n,m,s,t,ans;
bool use[maxn];
int q[maxm],head,tail;

void add(int x,int y,int c,int f){
    edge[++tol].f = f;
    edge[tol].c = c;
    edge[tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;

    edge[++tol].f = 0;
    edge[tol].c = -c;
    edge[tol].y = x;
    edge[tol].next = po[y];
    po[y] = tol;
}

bool spfa(){
    memset(use,false,sizeof(use));
    for(int i=0;i<=n;i++)
        dis[i] = inf;
    head = tail = 0;
    q[tail++] = s;
    dis[s] = 0;
    pre[s] = 0;
    int x,y;
    while(head<tail){
        x = q[head++];
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            y = edge[i].y;
            if(edge[i].f>0&&edge[i].c+dis[x]<dis[y]){
                dis[y] = edge[i].c+dis[x];
                pre[y] = i;
                if(!use[y]){
                    q[tail++] = y;
                    use[y] = true;
                }
            }
        }
    }
    if(dis[t]==inf)
        return false;
    int aug = inf;
    for(int i=pre[t];i;i=pre[edge[i^1].y])
        if(aug>edge[i].f)
            aug = edge[i].f;
    for(int i=pre[t];i;i=pre[edge[i^1].y]){
        edge[i].f -= aug;
        edge[i^1].f += aug;
    }
    ans += dis[t]*aug;
    return true;
}

int main(){
    freopen("sum.in","r",stdin);
    scanf("%d%d",&n,&m);
    int x,y,z;
    memset(po,0,sizeof(po));
    tol = 1;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z,1);
        add(y,x,z,1);
    }
    s = n+1;
    t = n+2;
    add(s,1,0,2);
    add(n,t,0,2);
    n = t;
    ans = 0;
    while(spfa());
    printf("%d\n",ans);

    return 0;
}

