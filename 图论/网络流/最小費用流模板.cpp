
const int MAXN = 1005;
const int MAXM = 100005;
const int INF = 1e9;

int pre[MAXN],dis[MAXN];
int po[MAXN],tol;
bool use[MAXN];
int q[MAXM],head,tail;
int n,m,s,t,ans;

struct node{
    int y,f,cost,next;
}edge[MAXM];

void Add(int x,int y,int f,int cost){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].cost = cost;
    edge[tol].next = po[x];
    po[x] = tol;
}

void add(int x,int y,int f,int cost){
    Add(x,y,f,cost);
    Add(y,x,0,-cost);
}

bool spfa(){
    memset(use,false,sizeof(use));
    rep1(i,t)
        dis[i] = INF;
    dis[s] = 0;
    head = tail = 0;
    q[tail++] = s;
    pre[s] = 0;
    while(head<tail){
        int x = q[head++];
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            int y = edge[i].y;
            if(edge[i].f>0&&edge[i].cost+dis[x]<dis[y]){
                dis[y] = dis[x]+edge[i].cost;
                pre[y] = i;
                if(!use[y]){
                    use[y] = true;
                    q[tail++] = y;
                }
            }
        }
    }
    if(dis[t]==INF)
        return false;

    int aug = INF;
    for(int i=pre[t];i;i=pre[edge[i^1].y])
        aug = min(aug,edge[i].f);
    for(int i=pre[t];i;i=pre[edge[i^1].y]){
        edge[i].f -= aug;
        edge[i^1].f += aug;
    }
    ans += dis[t]*aug;
    return true;
}
