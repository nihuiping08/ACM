/*

题目：
	赛车大赛的赛场由 N 颗行星和M条双向星际航路构成，其中每颗行星都有 一个不同的引力值。大赛要求车手们从
	一颗与这 N 颗行星之间没有任何航路的 天体出发，访问这 N 颗行星每颗恰好一次，首先完成这一目标的人获得
	胜利。 由于赛制非常开放，很多人驾驶着千奇百怪的自制赛车来参赛。这次悠悠驾 驶的赛车名为超能电驴，这
	是一部凝聚了全银河最尖端科技结晶的梦幻赛车。作 为最高科技的产物，超能电驴有两种移动模式：高速航行
	模式和能力爆发模式。 在高速航行模式下，超能电驴会展开反物质引擎，以数倍于光速的速度沿星际航 路高速
	航行。在能力爆发模式下，超能电驴脱离时空的束缚，使用超能力进行空 间跳跃——在经过一段时间的定位之
	后，它能瞬间移动到任意一个行星。 天不遂人愿，在比赛的前一天，超能电驴在一场离子风暴中不幸受损，机
	能 出现了一些障碍：在使用高速航行模式的时候，只能由每个星球飞往引力比它大 的星球，否则赛车就会发
	生爆炸。 尽管心爱的赛车出了问题，但是悠悠仍然坚信自己可以取得胜利。他找到了 全银河最聪明的贤者——
	你，请你为他安排一条比赛的方案，使得他能够用最少 的时间完成比赛。

分析：
	由于每个星球都得要访问一次，所以可以转化为最小费用流。
	拆点，如果有星际航路，连边 (a , b+n , 1 , w)
	对于直接跳跃的，连边 (s , i+n , 1 , w)
	
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
#define Clear(x) memset(x,0,sizeof(x))
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/

const int MAXN = 10005;
const int MAXM = 1000005;
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
            int now = edge[i].cost+dis[x];
            if(edge[i].f>0&&dis[y]>now){
                dis[y] = now;
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

    while(cin>>n>>m){
        int x,y,z;

        Clear(po);
        tol = 1;

        s = n<<1|1;
        t = n*2+2;

        rep1(i,n){
            RD(z);
            add( s,n+i,1,z );
            add( s,i,1,0 );
            add( n+i,t,1,0 );
        }

        while(m--){
            RD3(x,y,z);
            if(x>y) swap(x,y);
            add( x,y+n,1,z );
        }

        ans = 0;
        while(spfa())
            ;
        cout<<ans<<endl;
    }

	return 0;
}
