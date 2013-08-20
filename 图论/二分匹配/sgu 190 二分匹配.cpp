/*

题目：用2*1的方块覆盖n个方格。
分析：建模之后，就是裸的最大二分匹配

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
#include <utility>
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
/*

#pragma comment(linker, "/STACK:1024000000,1024000000")

int size = 256 << 20; // 256MB
char *p = (char*)malloc(size) + size;
__asm__("movl %0, %%esp\n" :: "r"(p) );

*/

/******** program ********************/

const int MAXN = 2000;

bool a[50][50];

int n,m;

int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};

bool use[MAXN];
int ym[MAXN];
int n2;

vector<int> adj[MAXN];

bool dfs(int x){
    foreach(i,adj[x]){
        int y = adj[x][i];
        if(!use[y]){
            use[y] = true;
            if(ym[y]==-1||dfs(ym[y])){
                ym[y] = x;
                return true;
            }
        }
    }
    return false;
}

bool hungry(){
    memset(ym,-1,sizeof(ym));

    int ret = 0;
    rep1(x,n2){
        Clear(use);
        ret += dfs(x);
    }
    //cout<<"max_pipei =  "<<ret<<endl;
    return ret==(n2-m)/2;
}

int id(int x,int y){
    return x*n+y-n;
}

bool solve(){

    n2 = n*n;
    rep1(i,n2)
        adj[i].clear();

    rep1(i,n){
        rep1(j,n){
            if( (i+j)%2 && !a[i][j]){
                rep(d,4){
                    int x = i+dx[d];
                    int y = j+dy[d];
                    if(x&&y&&x<=n&&y<=n&&!a[x][y])
                        adj[ id(i,j) ].pb( id(x,y) );
                }
            }
        }
    }

    bool ok = hungry();
    if(!ok)return false;
    puts("Yes");

    vector<PII> veca;
    vector<PII> vecb;

    rep1(i,n){
        rep1(j,n){
            if( !a[i][j]&&(i+j)%2==0 ){

                int x = id(i,j);
                int y = ym[x];
                //cout<<i<<" "<<j<<" "<<x<<" "<<y<<endl;

                if(y==x-1)
                    veca.pb( MP(i,j-1) );
                else if(y==x+1)
                    veca.pb( MP(i,j) );
                else if(y==x+n)
                    vecb.pb( MP(i,j) );
                else
                    vecb.pb( MP(i-1,j) );
            }
        }
    }


    if(vecb.size()){
        cout<<vecb.size()<<endl;
        foreach(i,vecb)
            printf("%d %d\n",vecb[i].first,vecb[i].second);
    }



    if(veca.size()){
        cout<<veca.size()<<endl;
        foreach(i,veca)
            printf("%d %d\n",veca[i].first,veca[i].second);
    }

    return true;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m){
        Clear(a);
        int x,y;
        rep(i,m){
            RD2(x,y);
            a[x][y] = true;
        }
        if( ((n*n-m)&1)||!solve() )
            puts("No");
    }

	return 0;
}
