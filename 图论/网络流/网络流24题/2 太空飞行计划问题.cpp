/*

题目：
    二分图中，x部为实验，y部位仪器。每个实验会有pi的利润，但是需要k个仪器，每
    个仪器的价格为ai。问如何安排实验，使得利润最大

分析：
    对于实验，建立超级源点连上实验，流量为pi。
    对于仪器，建立超级汇点连上仪器，流量为ai。
    对于每个实验需要的仪器，连上一条流量无穷的边。
    求最小割即为最大利润。

    输出路径：在残余网络上，按照流量大于0的边往下走，由于是有向图，所以能够走
    的就是需要的实验和仪器

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

const int MAXN = 1005;
const int MAXM = 100005;
const int INF = 1e9;

int gap[MAXN],dis[MAXN],arc[MAXN],cur[MAXN],pre[MAXN];
int po[MAXN],tol;
bool use[MAXN];
int n,m,s,t;

struct node{
    int y,f,next;
}edge[MAXM];

void Add(int x,int y,int f){
    edge[++tol].y = y;
    edge[tol].f = f;
    edge[tol].next = po[x];
    po[x] = tol;
}
void add(int x,int y,int f){
    Add(x,y,f);
    Add(y,x,0);
}

int sap(){
    memset(dis,0,sizeof(dis));
    memset(gap,0,sizeof(gap));
    gap[0] = t;
    rep1(i,t)
        arc[i] = po[i];

    int x = s;
    int ans = 0;
    int aug = INF;
    bool ok;

    while(dis[s]<t){
        //debug;
        cur[x] = aug;
        ok = false;
        for(int j=arc[x];j;j=edge[j].next){
            int y = edge[j].y;
            if(edge[j].f>0 && dis[y]+1==dis[x]){
                ok = true;
                arc[x] = pre[y] = j;
                aug = min(aug,edge[j].f);
                x = y;
                if(x==t){
                    ans += aug;
                    while(x!=s){
                        edge[pre[x]].f -= aug;
                        edge[pre[x]^1].f += aug;
                        x = edge[pre[x]^1].y;
                    }
                    aug = INF;
                }
                break;
            }
        }
        if(ok)
            continue;
        int MIN = t-1;
        for(int j=po[x];j;j=edge[j].next){
            int y = edge[j].y;
            if(edge[j].f>0&&dis[y]<MIN){
                MIN = dis[y];
                arc[x] = j;
            }
        }
        if(--gap[dis[x]]==0)
            break;
        dis[x] = MIN+1;
        ++ gap[dis[x]];
        if(x!=s){
            x = edge[pre[x]^1].y;
            aug = cur[x];
        }
    }
    return ans;
}

void dfs(int x){
    if(x==t)
        return;
    use[x] = true;
    for(int i=po[x];i;i=edge[i].next)
        if(edge[i].f>0&&!use[edge[i].y])
            dfs(edge[i].y);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD2(n,m)){
        memset(po,0,sizeof(po));
        tol = 1;

        int x;
        int sum = 0;

        s = n+m+1;
        t = s+1;

        rep1(i,n){
            RD(x);
            sum += x;
            add(s,i,x);
            while(getchar()!='\n'){
                RD(x);
                add(i,x+n,INF);
            }
        }

        rep1(i,m){
            RD(x);
            add(i+n,t,x);
        }

        int tmp = sap();

        memset(use,false,sizeof(use));
        dfs(s);
        bool ok = false;
        rep1(i,n)
            if(use[i]){
                ok?putchar(' '):ok = true;
                cout<<i;
            }
        cout<<endl;
        ok = false;
        for(int i=n+1;i<s;i++)
            if(use[i]){
                ok?putchar(' '):ok = true;
                cout<<i-n;
            }
        cout<<endl;

        sum -= tmp;
        cout<<sum<<endl;
    }

	return 0;
}

