/*

題目：
    現在有n塊地，每塊地為Jhon,Tom,空地三者其中之一。現在Jhon的奶牛對
    Tom的奶牛進行攻擊，並且每個時刻每塊地只能夠有一頭奶牛，每頭奶牛
    最多只能夠移動一塊地，從而對相鄰的奶牛進行攻擊，攻擊之後兩塊地均
    不能夠繼續使用。問最多Jhon能夠攻擊多少頭Tom的奶牛
分析：
    由於每塊地每個時刻最多只能夠有一頭奶牛，所以需要拆點進行約束。
    由於每塊地所在的奶牛可以是原地不動，可以是走到相鄰空地對空地的相鄰
    位置進行攻擊，所以我們需要額外增加一個點表示是否是原地不動。
    所以我們建模如下：
    1.對Jhon進行拆點，拆成J1，J2，J3。
    2.對空地進行拆點，拆成E1，E2
        1.S  --T1
        2.T1 --E1               如果x,y中為EJ(JE)
        3.J1 --J_y2,J_y1--J2    如果x,y為JJ
        3.J3 --Tom              如果x,y為(JT)
        4.E2 -Tom               如果x,y為ET
        5.Tom--T

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

#define lx(x) (x<<1)
#define rx(x) (x<<1|1)
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


const int MAXN = 5005;
const int MAXM = 100005;
const int INF = 1e9;

int po[MAXN],tol;
int gap[MAXN],dis[MAXN],arc[MAXN],pre[MAXN],cur[MAXN];
char c[MAXN];
int id[MAXN];
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

    RD2(n,m);
    scanf("%s",c+1);
    int x,y;

    s = 5000;
    t = s+1;
    tol = 1;

    int Em = 0,Jhon = 0,Tom = 0;
    rep1(i,n){
        if(c[i]=='E')
            id[i] = ++ Em;
        else if(c[i]=='J')
            id[i] = ++ Jhon;
        else
            id[i] = ++ Tom;
    }

    int e1 = Jhon*3;
    int e2 = Jhon*3+Em;
    int tot = Jhon*3+Em*2;

    while(m--){
        RD2(x,y);
        if(c[x]=='T')
            swap(x,y);

        if(c[x]=='J'){
            if(c[y]=='J'){
                add(id[x],id[y]+Jhon,1);
                add(id[y],id[x]+Jhon,1);
            }else if(c[y]=='E')
                add(id[x],id[y]+e1,1);
            else
                add(id[x]+2*Jhon,id[y]+tot,1);
        }else if(c[x]=='E'){
            if(c[y]=='J')
                add(id[y],id[x]+Jhon*3,1);
            else if(c[y]=='T')
                add(id[x]+e2,id[y]+tot,1);
        }
    }

    rep1(i,Jhon){
        add(s,i,1);
        add(i,i+Jhon,1);
        add(i+Jhon,i+Jhon*2,1);
    }

    rep1(i,Em)
        add(i+e1,i+e2,1);

    rep1(i,Tom)
        add(i+tot,t,1);

    cout<<sap()<<endl;

	return 0;
}
