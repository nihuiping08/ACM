/*

数据貌似有误。。。二分上限设置成inf死都过不了。。。

详细解释一下。
为避免负数，时间计数1～24。令：
R[i] i时间需要的人数 （1<=i<=24）
T[i] i时间应聘的人数 （1<=i<=24）
x[i] i时间录用的人数 （0<=i<=24），其中令x[0]=0
再设s[i]=x[0]+x[1]+……+x[i] （0<=i<=24），
由题意，可得如下方程组：
(1) s[i]-s[i-8]>=R[i]        (8<=i<=24)
(2) s[i]-s[16+i]>=R[i]-s[24] (1<=i<=7)
(3) s[i]-s[i-1]>=0           (1<=i<=24)
(4) s[i-1]-s[i]>=-T[i]       (1<=i<=24)

这个差分约束有个特殊的地方，(2)的右边有未知数s[24]。
这时可以通过枚举s[24]=ans来判断是否有可行解。
即(2)变形为(2') s[i]-s[16+i]>=R[i]-ans (1<=i<=7)
再通过SPFA求解(1)(2')(3)(4)。

不过最后有可能出现这种情况：
(1)(2')(3)(4)虽然有解，但求出的s[24]小于代入(2')里的ans！
这时，显然得到的s[]不满足原来的(2)了（请仔细比较(2)与(2')）。
不过虽然得到的解不满足原方程组，但这并不代表(1)(2)(3)(4)在s[24]=ans时没有可行解！
此外，值得注意的是，当得到的s[24]>ans时，虽然s[24]不一定是最优解，但把ans置成s[24]后，确实是可行解。

所以，简单把(2)置换成(2')是有问题的！
为了等价原命题，必须再加上条件：s[24]>=ans
这就是所谓加出来的那条边（5） s[24]－s[0]>=ans

最后说一下，SPFA后判dis[24]==ans其实是没有必要的。


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

const int MAXN = 25;
const int INF = 1e9;
const int n = 24;

vector< PII > adj[MAXN];
int dis[MAXN];
bool use[MAXN];
int id[MAXN];
int r[MAXN],w[MAXN];

void build(int ans){
    rep(i,n+1)
        adj[i].clear();
    rep1(i,24){
        adj[i-1].pb( MP(i,0) );
        adj[i].pb( MP(i-1,-w[i]) );
    }
    rep1(i,8)
        adj[i+16].pb( MP(i,r[i]-ans) );
    REP(i,9,24)
        adj[i-8].pb( MP(i,r[i]) );

    adj[0].pb( MP(24,ans) );
}

bool spfa(int mid){
    build(mid);

    memset(use,false,sizeof(use));
    memset(id,0,sizeof(id));
    fill( dis,dis+25,-INF );

    dis[0] = 0;
    id[0] = 1;

    queue<int> q;
    q.push(0);
    while(q.size()){
        int x = q.front();
        q.pop();
        use[x] = false;
        foreach(i,adj[x]){
            int y = adj[x][i].first;
            int t = adj[x][i].second+dis[x];
            if(dis[y]<t){
                dis[y] = t;
                if(!use[y]){
                    if(++id[y]>25)return false;
                    use[y] = true;
                    q.push(y);
                }
            }
        }
    }
    return dis[24]==mid;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    while(ncase--){
        rep1(i,n)
            RD(r[i]);
        int x,m;
        RD(m);
        Clear(w);
        rep(i,m){
            RD(x);
            w[x+1] ++;
        }

        int ans = -1;
        int l = 0 , r = m+1;
        while(l<=r){
            int mid = (l+r)>>1;
            if(spfa(mid)){
                ans = mid;
                r = mid-1;
            }else
                l = mid+1;
        }

        //cout<<ans<<endl;
        if(~ans)
            cout<<ans<<endl;
        else
            puts("No Solution");
    }

	return 0;
}
