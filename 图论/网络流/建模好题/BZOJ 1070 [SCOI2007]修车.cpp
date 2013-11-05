/*

题目：
    同一时刻有N位车主带着他们的爱车来到了汽车维修中心。维修中心共有M位技术人
    员，不同的技术人员对不同的车进行维修所用的时间是不同的。现在需要安排这M
    位技术人员所维修的车及顺序，使得顾客平均等待的时间最小。
    说明：顾客的等待时间是指从他把车送至维修中心到维修完毕所用的时间。

分析：
    1.把每个人拆成m个点，(i,j)表示第i个人修倒数第j轮修车。
    2.然后考虑点(i,j)，每辆车都连上该点，费用为j*t[k][i]。因为这辆车对于后面的
    时间贡献是：后面所有的车都等待了这么长的时间。
    3.得要建立n个节点，表示第i辆车，连上源点。
    4.对于每个(i,j)节点，连上汇点。

*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int INF = 1e9;
const int MAXN = 605;
const int MAXM = 100005;

int pre[MAXN],dis[MAXN];
int po[MAXN],tol;
bool use[MAXN];
int q[MAXM],head,tail;
int T[62][11];
int n,m,s,t,ans;

struct node{
    int y,f,cost,next;
}edge[MAXM];

void add(int x,int y,int f,int cost){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].cost = cost;
    edge[tol].next = po[x];
    po[x] = tol;

    edge[++tol].y = x;
    edge[tol].f = 0;
    edge[tol].cost = -cost;
    edge[tol].next = po[y];
    po[y] = tol;
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

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>m>>n){

        memset(po,0,sizeof(po));
        tol = 1;

        rep1(i,n)
            rep1(j,m)
                RD(T[i][j]);

        s = n*m+n+1;
        t = s+1;

        rep1(i,n)
            add(s,i,1,0);

        int tot = n;

        rep1(i,m) // 第i位技术人员
            rep1(j,n){ // 倒数第j轮
                add(++tot,t,1,0);
                rep1(k,n) // 第k辆车
                    add(k,tot,1,j*T[k][i]);
            }

        ans = 0;
        while(spfa())
            ;
        printf("%.2lf\n",double(ans)/n);
    }

	return 0;
}
