/*

1. 选择自己的一张牌X，这张牌之前没有用过
2. 如果Jiro没有手牌，那么他被伤害X
3. 否则由Ciel选择Jiro的一张手牌Y：
   * Y的position为Attack，那么必须有(X's strength) >= (Y's strength)，
	Jiro获得伤害(X's strength)-(Y's strength)，手牌Y不可以再用
   * Y的position为Defense，那么必须有(X's strength) > (Y's strength)，
	Jiro没有伤害，手牌Y不可以再用	最小费用流or贪心。

   
最小费用流分两种情况：
不全部耗尽Jiro的手牌时，直接对于图建边即可，需要把Ciel的所有手牌连上汇点。
全部耗尽Jiro的手牌时，需要建立虚拟的节点表示Jiro的手牌，表示题目描述中的第2种情况。
对于每种情况，求一遍最小费用流。

*/
#include <set>
#include <map>
#include <list>
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
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)
#define All(vec) vec.begin(),vec.end()
#define MP make_pair
#define PII pair<int,int>
#define PQ priority_queue
#define cmax(x,y) x = max(x,y)
#define cmin(x,y) x = min(x,y)
#define fir first
#define sec second
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/

const int MAXN = 1005;
const int MAXM = 100005;
const int INF = 1e9;

int pre[MAXN],dis[MAXN];
int po[MAXN],tol;
bool use[MAXN];
int q[MAXM],head,tail;
pair<int,string> b[MAXN];
int a[MAXN];
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

int killAll(){
    s = n<<1|1;
    t = s+1;
    memset(po,0,sizeof(po));
    tol = 1;

    //sort(b+1,b+n+1);
    //reverse( b+1,b+n+1 );

    rep1(i,n)
        add( s,i,1,0 );
    rep1(i,n)
        add( i+n,t,1,0 );

    rep1(i,n){
        rep1(j,n){
            if(j>m)
                add( i,j+n,1,-a[i] );
            else{
                if( b[j].second=="ATK" ){
                    if(b[j].first<=a[i])
                        add( i,j+n,1,-(a[i]-b[j].first) );
                }else if(b[j].first<a[i])
                    add(i,j+n,1,0);
            }
        }
    }

    ans = 0;
    while(spfa())
        ;

    int tmp = 0;
    for(int i=po[t];i;i=edge[i].next)
        if(edge[i].f>0)
            tmp ++;
    if(tmp!=n)return 0;
    //cout<<"max_flow = "<<tmp<<endl<<endl;

    return -ans;
}

int notKillAll(){
    memset(po,0,sizeof(po));
    tol = 1;

    s = n+m+1;
    t = s+1;

    rep1(i,n){
        add( s,i,1,0 );
        add( i,t,1,0 );
    }
    rep1(j,m)
        add( j+n,t,1,0 );

    rep1(i,n)
        rep1(j,m)
            if(b[j].second=="ATK")
                if(b[j].first<a[i])
                    add( i,j+n,1, -(a[i]-b[j].first) );

    ans = 0;
    while(spfa())
        ;
    return -ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase = 0;
    while(cin>>m>>n){
        ncase?puts("-----------------"):ncase = 1;
        rep1(i,m)
            cin>>b[i].second>>b[i].first;
        rep1(i,n)
            RD(a[i]);

        int tmp = notKillAll();
        //cout<<"not   "<<t<<endl<<endl;
        if( n>m )
            cmax( tmp,killAll() );
        cout<< tmp <<endl;
    }

	return 0;
}
