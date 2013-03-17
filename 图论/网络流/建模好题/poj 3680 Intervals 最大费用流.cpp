/*

题目：
    每个开区间有权值，选择一些开区间，使得每个数都不会有超过k的区间覆盖，求
    剩下可能的最大权值。
分析：
    先离散化，然后i跟i+1的点连线，流量为k，费用0。
    建立超级源点s，连上点1，费用0，流量为k。
    建立超级汇点t，连上n，费用0，流量k。
    对于每个区间i，连两个区间离散后的id，费用-ci，流量为1。

    为什么这样建模？
    首先，离散化之后相邻的两个区间是不会相互覆盖的。所以我们总可以建立超级源点
    连上1，经过所有的点，流向超级汇点。从而使得每个数的最大区间覆盖数不会超过
    k。

*/
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <string>
#include <vector>
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

const int MAXN = 1005;
const int MAXM = 100005;
const int INF = 1e9;

int po[MAXN],tol;
int pre[MAXN],dis[MAXN];
bool use[MAXN];
int a[MAXN],b[MAXN],c[MAXN],p[MAXN];
int q[MAXM],head,tail;
int n,m,s,t,ans;

struct node{
    int y,next,f,cost;
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
    rep(i,1000)
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

    int ncase;
    RD(ncase);
    while(ncase--){
        RD2(n,m);

        memset(po,0,sizeof(po));
        tol = 1;
        s = n*2|1;
        t = s+1;

        int tot = 0;
        rep(i,n){
            RD3(a[i],b[i],c[i]);
            p[tot++] = a[i];
            p[tot++] = b[i];
        }

        sort(p,p+tot);
        map<int,int> ma;
        ma[p[0]] = 1;
        int cnt = 1;
        for(int i=1;i<tot;i++){
            if(p[i]==p[i-1])
                continue;
            ma[p[i]] = ++cnt;
        }

        rep1(i,tot-1)
            add(i,i+1,m,0);

        rep(i,n){
            int x = ma[a[i]];
            int y = ma[b[i]];
            add(x,y,1,-c[i]);
        }

        add(s,1,m,0);
        add(tot,t,m,0);
        ans = 0;


        while(spfa())
            ;
        cout<<-ans<<endl;
    }

	return 0;
}
