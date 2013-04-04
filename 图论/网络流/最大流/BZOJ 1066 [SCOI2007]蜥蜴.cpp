/*

同：POJ 2711

題目：
    在一个r行c列的网格地图中有一些高度不同的石柱，一些石柱上站着一些蜥
    蜴，你的任务是让尽量多的蜥蜴逃到边界外。 每行每列中相邻石柱的距离
    为1，蜥蜴的跳跃距离是d，即蜥蜴可以跳到平面距离不超过d的任何一个石
    柱上。石柱都不稳定，每次当蜥蜴跳跃时，所离开的石柱高度减1（如果仍
    然落在地图内部，则到达的石柱高度不变），如果该石柱原来高度为1，则
    蜥蜴离开后消失。以后其他蜥蜴不能落脚。任何时刻不能有两只蜥蜴在同一
    个石柱上。

分析：
    我們可以發現，從一個點跳到另一個有石柱的點的次數就是兩者中最小的值。
    所以我們可以進行拆點，把每個石柱拆成兩個，然後流量為石柱原始高度。
    然後對於可以連邊的直接連邊。跑一次最大流即可

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
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

/******** program ********************/

const int MAXN = 1005;
const int MAXM = 100005;
const int INF = 1e9;

int po[MAXN],tol;
int gap[MAXN],dis[MAXN],arc[MAXN],pre[MAXN],cur[MAXN];
char str[22][22];
int n,m,s,t,d;

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

int Abs(int x){
    return max(x,-x);
}

int sap(){
    memset(dis,0,sizeof(dis));
    memset(gap,0,sizeof(gap));
    gap[0] = t;
    rep1(i,t)
        arc[i] = po[i];

    int ans = 0;
    int aug = INF;
    int x = s;

    while(dis[s]<t){
        bool ok = false;
        cur[x] = aug;
        for(int i=arc[x];i;i=edge[i].next){
            int y = edge[i].y;
            if(edge[i].f>0&&dis[y]+1==dis[x]){
                ok = true;
                pre[y] = arc[x] = i;
                aug = min(aug,edge[i].f);
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
        for(int i=po[x];i;i=edge[i].next)
            if(edge[i].f>0&&dis[edge[i].y]<MIN){
                MIN = dis[edge[i].y];
                arc[x] = i;
            }
        if(--gap[dis[x]]==0)
            break;
        dis[x] = ++ MIN;
        ++ gap[dis[x]];
        if(x!=s){
            x = edge[pre[x]^1].y;
            aug = cur[x];
        }
    }
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD3(n,m,d)){
        memset(po,0,sizeof(po));
        tol = 1;
        s = n*m<<1|1;
        t = s+1;
        int tmp = n*m;

        rep1(i,n)
            scanf("%s",str[i]+1);
        rep1(i,n){
            rep1(j,m){
                if(str[i][j]>'0'){
                    int x = i*m-m+j;
                    add(x,x+tmp,str[i][j]-'0');
                    for(int p=-d;p<=d;p++)
                        for(int q=-d;q<=d;q++){
                            int px = i+p , py = j+q;
                            if(px<1||py<1||px>n||py>m)
                                continue;
                            if(str[px][py]=='0'||Abs(p)+Abs(q)>d)
                                continue;
                            add(x+tmp,px*m-m+py,INF);
                        }
                }
            }
        }

        rep1(i,n)
            rep1(j,m)
                if(str[i][j]>'0')
                    if(i<=d||j<=d||n-i+1<=d||m-j+1<=d)
                        add(i*m-m+j+tmp,t,INF);

        rep1(i,n)
            scanf("%s",str[i]+1);
        int ans = 0;
        rep1(i,n)
            rep1(j,m)
                if(str[i][j]=='L'){
                    add(s,i*m-m+j,1);
                    ans ++;
                }
        cout<<ans-sap()<<endl;
    }

	return 0;
}
