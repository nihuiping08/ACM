/*

题目：
    传纸条

分析：
    对每个格点进行拆点(i,i+temp)，然后每对点之间连上流量为1的边，
    费用为格点的权值，另外对于相邻可走的格子进行连边，为
    (temp+i,i+m),(temp+i,i+1)，费用为0且流量为1。注意左上以及右下
    的流量为2

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int X = 51;
const int maxn = X*X*2;
const int maxm = maxn*4;
const int inf = 1e8;
#define debug puts("here");

struct node{
    int y,c,f,next;
}edge[maxm];

int arc[maxn],dis[maxn],pre[maxn];
int po[maxn],tol;
int n,m,s,t,ans;
bool use[maxn];
int q[maxm],head,tail;

bool spfa(){
    memset(use,false,sizeof(use));
    head = tail = 0;
    q[tail++] = s;
    for(int i=1;i<=n;i++)
        dis[i] = inf;
    dis[s] = 0;
    pre[s] = 0;
    int x,y;
    while(head<tail){
        x = q[head++];
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            y = edge[i].y;
            if(edge[i].f>0&&edge[i].c+dis[x]<dis[y]){
                dis[y] = dis[x]+edge[i].c;
                pre[y] = i;
                if(!use[y]){
                    use[y] = true;
                    q[tail++] = y;
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
    ans += aug*dis[t];
    return true;
}

void add(int x,int y,int c,int f){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].c = c;
    edge[tol].next = po[x];
    po[x] = tol;

    edge[++tol].y = x;
    edge[tol].f = 0;
    edge[tol].c = -c;
    edge[tol].next = po[y];
    po[y] = tol;
}

void build(){
    int x,y;
    int temp = n*m;
    s = 1;
    t = temp*2;

    tol = 1;
    memset(po,0,sizeof(po));

    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            scanf("%d",&y);
            x = i*m+j-m;
            //cout<<x<<" "<<temp+x<<endl;
            y = -y;
            if(x==1||x==temp)
                add(x,x+temp,y,2);
            else
                add(x,x+temp,y,1);
        }

    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            x = i*m-m+j+temp;
            if(i<n){
                y = i*m+j;
                add(x,y,0,1);
                //cout<<"dowm  "<<x<<" "<<y<<endl;
            }
            if(j<m){
                y = x-temp+1;
                add(x,y,0,1);
                //cout<<"right  "<<x<<" "<<y<<endl;
            }
        }
    //for(int i=2;i<=tol;i++)
    //    cout<<edge[i^1].y<<" "<<edge[i].y<<" "<<edge[i].c<<" "<<edge[i].f<<endl;
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m){
        build();
        n = n*m*2;
        ans = 0;
        while(spfa());
        printf("%d\n",-ans);
    }
    return 0;
}
