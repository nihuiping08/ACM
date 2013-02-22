#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int X = 1005;

struct node{
    int y,next;
}edge[X*2];

int po[X],tol;
int dis[X],pre[X][X];
double dp[X][X];
bool use[X][X];
int id[X];
int n,m;

void add(int x,int y){
    edge[++tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

void apsp(){
    for(int k=1;k<=n;k++){
        memset(dis,-1,sizeof(dis));
        dis[k] = 0;
        int head = 0,tail = 0;
        int q[X];
        q[tail++] = k;
        pre[k][k] = k;
        while(head<tail){
            int x = q[head++];
            for(int i=po[x];i;i=edge[i].next){
                int y = edge[i].y;
                if(dis[y]==-1){
                    pre[y][k] = x;
                    dis[y] = dis[x]+1;
                    q[tail++] = y;
                }
                else if(dis[y]==dis[x]+1)
                    pre[y][k] = min(pre[y][k],x);
            }
        }
    }
}

double f(int s,int t){
    if(use[s][t])
        return dp[s][t];

    use[s][t] = true;

    if(s==t)
        return dp[s][t] = 0;

    double ans = 0;
    int x = pre[pre[s][t]][t];
    ans = f(x,t)+1;

    if(x==t)
        return dp[s][t] = ans;

    for(int i=po[t];i;i=edge[i].next)
        ans += f(x,edge[i].y)+1;
    return dp[s][t] = ans/(id[t]+1);
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m){
        int x,y,s,t;
        cin>>s>>t;
        memset(po,0,sizeof(po));
        memset(id,0,sizeof(id));
        tol = 0;
        while(m--){
            scanf("%d%d",&x,&y);
            add(x,y);
            add(y,x);
            id[x] ++;
            id[y] ++;
        }
        apsp();
        memset(use,false,sizeof(use));
        printf("%.3lf\n",f(s,t));
    }
    return 0;
}
