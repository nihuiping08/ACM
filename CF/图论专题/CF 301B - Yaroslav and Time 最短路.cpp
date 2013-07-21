/*

分析：变形的最短路。

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

/******** program ********************/

const int MAXN = 105;
const ll INF = 1e15;

ll dis[MAXN];
ll g[MAXN][MAXN];
bool use[MAXN];
ll val[MAXN];
int id[MAXN];
int n,d;

bool spfa(){
    queue<int> q;
    q.push(1);

    rep1(i,n)
        dis[i] = INF;
    dis[1] = 0;
    memset(id,0,sizeof(id));

    while(!q.empty()){
        int x = q.front();
        q.pop();

        use[x] = false;
        rep1(y,n){
            ll t = dis[x]+g[x][y]-val[x];
            if(t<dis[y]){
                dis[y] = t;
                if(!use[y]){
                    //cout<<x<<" "<<y<<" "<<dis[y]<<" "<<dis[x]<<endl;
                    use[y] = true;
                    q.push(y);
                    id[y]++;
                    if(id[y]>=n)
                        return false;
                }
            }
        }
    }
    cout<<dis[n]<<endl;
    return true;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>d){
        int a[MAXN],b[MAXN];

        memset(val,0,sizeof(val));
        REP(i,2,n-1)
            cin>>val[i];

        rep1(i,n){
            RD2(a[i],b[i]);
            REP(j,1,i)
                g[i][j] = g[j][i] = d*( abs(a[i]-a[j])+abs(b[i]-b[j]) );
            g[i][i] = INF;
        }

        spfa();
    }

	return 0;
}
