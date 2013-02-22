/*

题目：
	描述 Description
    风景迷人的小城Y 市，拥有n 个美丽的景点。由于慕名而来的游客越来越多，Y 市特意安排了一辆观光公交车，
	为游客提供更便捷的交通服务。观光公交车在第 0 分钟出现在 1号景点，随后依次前往 2、3 、4 ……n 号景点。
	从第 i 号景点开到第 i+1 号景点需要 Di 分钟。
	任意时刻，公交车只能往前开，或在景点处等待。 
    设共有m 个游客，每位游客需要乘车1 次从一个景点到达另一个景点，第i 位游客在Ti 分钟来到景点 Ai ，希望乘
	车前往景点Bi （Ai<Bi ）。为了使所有乘客都能顺利到达目的地，公交车在每站都必须等待需要从该景点出发的
	所有乘客都上车后才能出发开往下一景点。假设乘客上下车不需要时间。  
    一个乘客的旅行时间，等于他到达目的地的时刻减去他来到出发地的时刻。因为只有一辆观光车，有时候还要停下来
	等其他乘客，乘客们纷纷抱怨旅行时间太长了。于是聪明的司机ZZ给公交车安装了 k 个氮气加速器，每使用一个加
	速器，可以使其中一个 Di 减1 。对于同一个Di 可以重复使用加速器，但是必须保证使用后Di 大于等于0 。 
    那么ZZ该如何安排使用加速器，才能使所有乘客的旅行时间总和最小？ 
	
输入格式 Input Format
    第1 行是3 个整数n, m, k ，每两个整数之间用一个空格隔开。分别表示景点数、乘客数和氮气加速器个数。 
    第2 行是n-1 个整数，每两个整数之间用一个空格隔开，第i 个数表示从第i 个景点开往第i+1 个景点所需要的时
	间，即 Di 。 
    第3 行至m+2 行每行3 个整数 Ti , Ai, Bi，每两个整数之间用一个空格隔开。第 i+2 行表示第i 位乘客来到出
	发景点的时刻，出发的景点编号和到达的景点编号。 
	
分析：
	最小费用流的建模好题。

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define debug puts("here");

const int maxn = 2005;
const int maxm = 20005;
const int inf = ~0u>>1;

struct node{
    int y,next;
    int f;
    int c;
}edge[maxm];

int pre[maxn],po[maxn],tol;
int dis[maxn];
int q[maxm];
bool use[maxn];
int la[maxn],num[maxn],d[maxn];
int n,m,k,s,t;
int ans;

void add(int x,int y,int f,int c){
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
    int head = 0,tail = 0;
    for(int i=0;i<=n;i++)
        dis[i] = inf;
    dis[s] = 0;
    q[tail++] = s;
    pre[s] = 0;
    int x,y;
    while(head<tail){
        x = q[head++];
        use[x] = false;
        for(int i=po[x];i;i=edge[i].next){
            y = edge[i].y;
            if(edge[i].f>0&&edge[i].c+dis[x]<dis[y]){
                dis[y] = edge[i].c + dis[x];
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
    ans += dis[t]*aug;
    return true;
}

int build(){
    memset(la,0,sizeof(la));
    memset(po,0,sizeof(po));
    memset(num,0,sizeof(num));
    tol = 1;

    int ti,ai,bi;
    int sum = 0;

    for(int i=2;i<=n;i++)
        scanf("%d",&d[i]);

    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&ti,&ai,&bi);
        la[ai] = max(la[ai],ti);
        num[bi]++;
        sum += ti;
    }

    s = 2*n+3;
    int tt = n<<1|1;
    t = tt+1;

    for(int i=1;i<=n;i++){
        if(i!=1){
            add(s,i,la[i-1]+d[i],0);
            add(i+n,t,la[i],0);
            add(i,tt,d[i],0);
        }
        if(i!=n)
            add(i+n,i+1,inf,0);
        add(i,i+n,inf,num[i]);
    }
    add(n<<1,t,inf,0);
    add(tt,t,k,0);
    n = t+1;
    return sum;
}

int main(){
    freopen("sum.in","r",stdin);
    while(cin>>n>>m>>k){
        ans = -build();
        while(spfa());
        cout<<ans<<endl;
    }
    return 0;
}
