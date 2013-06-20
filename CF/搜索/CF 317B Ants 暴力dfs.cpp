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

/******** program ********************/

const int MAXN = 131;
const int ox = 65;
const int oy = 65;

int a[MAXN][MAXN],b[MAXN][MAXN];

int dx[] = {0,0,-1,1};
int dy[] = {1,-1,0,0};

void init(){
    memset(b,0,sizeof(b));
    int p = MAXN-1;
    bool ok = false;
    rep1(i,p)
        rep1(j,p)
            if(a[i][j]>3){
                rep(k,4)
                    b[ i+dx[k]  ][ j+dy[k] ] += a[i][j]/4;
                b[i][j] -= a[i][j]/4*4;
            }
    rep1(i,p)
        rep1(j,p){
            a[i][j] += b[i][j];
            if(a[i][j]>3)
                ok = true;
        }
    if(ok)
        init();
}

int main(){

#ifndef ONLINE_JUDGE
freopen("sum.in","r",stdin);
//freopen("sum.out","w",stdout);
#endif

    int n,m,x,y;
    while(cin>>n>>m){
		memset(a,0,sizeof(a));
        a[ox][oy] = n;
        init();

        while(m--){
            RD2(x,y);
            x += ox;
            y += oy;
            if(x>=MAXN||y>=MAXN||x<0||y<0)
                puts("0");
            else
                printf("%d\n",a[x][y]);
        }
    }

return 0;
}