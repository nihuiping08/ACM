/*

题目：
    给定一张有向图，每条边都有一个容量C和一个扩容费用W。这里扩容费用是指将容
    量扩大1所需的费用。求：
    1、	在不扩容的情况下，1到N的最大流；
    2、	将1到N的最大流增加K所需的最小扩容费用。

分析：
    第一问就是求一遍最大流
    第二问，在第一问的基础上建立最小费用流（流量为输入，费用0），表示原来存在
    的道路。
    然后再添加多m条的边，流量为inf，费用为扩建时的费用。
    最后跑一次最小费用最大流即可

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
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

const int INF = 1e9;
const int MAXN = 1005;
const int MAXM = 50005;

int pre[MAXN],dis[MAXN];
int po[MAXN],tol;
bool use[MAXN];
int q[MAXM],head,tail;
int lx[MAXM],ly[MAXM],lc[MAXM],lw[MAXM];
int n,m,s,t,ans,ff;

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
    ff += aug;
    ans += dis[t]*aug;
    return true;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int kk;
    RD3(n,m,kk);

    tol = 1;
    rep(i,m){
        RD4(lx[i],ly[i],lc[i],lw[i]);
        add(lx[i],ly[i],lc[i],0);
    }

    s = 1,t = n;
    ans = ff = 0;
    while(spfa())
        ;
    cout<<ff<<" ";

    rep(i,m)
        add(lx[i],ly[i],INF,lw[i]);
    t = n+1;
    add(n,t,kk,0);
    ans = 0;
    while(spfa())
        ;
    cout<<ans<<endl;
	return 0;
}
