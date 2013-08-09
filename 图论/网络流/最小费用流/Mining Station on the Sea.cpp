/*

题目：
    有n个船的摆放地点、m个港口，给出n艘船开始时停放的港口位置，然
    后给出k组港口与港口之间的路径关系，再给出p组船与港口的关系，现
    在问如何安排船，使得船从港口回到船的摆放地点

分析：
    直接对原图进行建图，求一遍最小费用流即可
    或者先对船以及港口跑一次floyd，注意松弛的时候只能够以港口作为
    中间节点（控制最外层循环即可），然后跑一次km(若是费用流的话，
    会RE...）

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int X = 1005;
const int maxn = 100005;
const int maxm = 3000005;
const int inf = 1e9;
#define debug puts("here");

int dis[maxn],pre[maxn],arc[maxn];
int po[maxn],tol;
bool use[maxn];
int map[X][X];
int n,m,s,t,k,p,ans;
int d[maxn];

struct node{
    int y,f,c,next;
}edge[maxm];

void add(int x,int y,int c,int f){
    edge[++tol].y = y;
    edge[tol].c = c;
    edge[tol].f = f;
    edge[tol].next = po[x];
    po[x] = tol;

    edge[++tol].y = x;
    edge[tol].c = -c;
    edge[tol].f = 0;
    edge[tol].next = po[y];
    po[y] = tol;
}

bool spfa(){
    memset(use,false,sizeof(use));
    for(int i=1;i<=n;i++)
        dis[i] = inf;
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    pre[s] = 0;
    int x,y;
    while(q.size()){
        x = q.front();
        q.pop();
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            y = edge[i].y;
            if(edge[i].f>0&&edge[i].c+dis[x]<dis[y]){
                dis[y] = edge[i].c + dis[x];
                pre[y] = i;
                if(!use[y]){
                    use[y] = true;
                    q.push(y);
                }
            }
        }
    }
    if(dis[t]==inf)
        return false;
    int aug = inf;
    for(int i=pre[t];i;i=pre[edge[i^1].y])
        aug = min(aug,edge[i].f);
    for(int i=pre[t];i;i=pre[edge[i^1].y]){
        edge[i].f -= aug;
        edge[i^1].f += aug;
    }
    ans += dis[t]*aug;
    return true;
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m>>k>>p){
        int x,y,z;
        s = n+m+1;
        t = s+1;
        tol = 1;
        memset(po,0,sizeof(po));
        for(int i=1;i<=n;i++){
            scanf("%d",&d[i]);
            add(s,d[i],0,1);
        }
        for(int i=1;i<=k;i++){
            scanf("%d%d%d",&x,&y,&z);
            add(x,y,z,inf);
            add(y,x,z,inf);
        }
        for(int i=1;i<=p;i++){
            scanf("%d%d%d",&x,&y,&z);
            add(y,x+m,z,inf);
        }
        for(int i=m+1;i<=n+m;i++)
            add(i,t,0,1);
        ans = 0;
        n = t;
        while(spfa())
            ;

        cout<<ans<<endl;
    }
    return 0;
}
