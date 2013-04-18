/*

題目：
	刪除樹的一條邊，然後再次加上任意一條邊使得樹聯通，並且新的樹的任意兩點之間的距離和最小
分析：
	n<=5000，可以先枚舉刪掉的是那條邊，然後再分別找出兩棵樹的重心，連接之後可以使得該值最小

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
const ll INF = 1e18;

int po[MAXN],sz[MAXN],tol,n;
bool use[MAXN<<1];

struct node{
    int y,val,next;
}edge[MAXN<<1];

void add(int x,int y,int v){
    edge[++tol].val = v;
    edge[tol].y = y;
    edge[tol].next = po[x];
    po[x] = tol;
}

void con(int x,int fa,int &s){ /// 找出每個聯通塊的大小
    s ++;
    for(int i=po[x];i;i=edge[i].next){
        if(use[i])  continue;
        int y = edge[i].y;
        if(y==fa)   continue;
        con(y,x,s);
    }
}

void dot(int x,int fa,int &core,int &d,int tot_sz){ /// 找出重心
    int mx = 0;
    int j = -1;
    sz[x] = 1;
    for(int i=po[x];i;i=edge[i].next){
        if(use[i])  continue;
        int y = edge[i].y;
        if(y==fa){
            j = i;
            continue;
        }
        dot(y,x,core,d,tot_sz);
        sz[x] += sz[y];
        mx = max(mx,sz[y]);
    }
    if(fa)
        mx = max(mx,tot_sz-sz[x]);
    //cout<<"------------------- "<<x<<" "<<mx<<endl;
    if(mx<d){
        d = mx;
        core = x;
    }
}

void cal(int x,int fa,ll &ans){
    sz[x] = 1;
    for(int i=po[x];i;i=edge[i].next){
        if(use[i])  continue;
        int y = edge[i].y;
        if(y==fa)   continue;
        cal(y,x,ans);
        sz[x] += sz[y];
        ans += sz[y]*ll(n-sz[y])*edge[i].val;
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int x,y,z;
    bool ok = false;
    while(~RD(n)){
        ok?puts("-----------------------"):ok = true;
        memset(po,0,sizeof(po));
        tol = 0;
        rep1(i,n-1){
            RD3(x,y,z);
            add(x,y,z);
            add(y,x,z);
        }
        memset(use,false,sizeof(use));
        ll ans = INF;

        for(int i=1;i<tol;i+=2){
            use[i] = use[i+1] = true;

            int x = edge[i+1].y , y = edge[i].y;
            int dx = x , dy = y;
            ll tmp = 0;
            int sa = 0 , sb = 0;

            con(x,0,sa);
            sb = n-sa;

            int d = 110000000;
            dot(x,0,dx,d,sa);
            d = 110000000;

            dot(y,0,dy,d,sb);

            cal(dx,0,tmp);
            cal(dy,0,tmp);
            tmp += ll(edge[i].val)*sz[dx]*sz[dy];

            /*
            cout<<x<<" "<<y<<" "<<va<<" "<<vb<<endl;
            cout<<dx<<" "<<dy<<endl;
            cout<<tmp<<endl;
            */

            ans = min(ans,tmp);

            use[i] = use[i+1] = false;
        }
        cout<<ans<<endl;
    }

	return 0;
}
