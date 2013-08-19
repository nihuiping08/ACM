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
/*

#pragma comment(linker, "/STACK:1024000000,1024000000")

int size = 256 << 20; // 256MB
char *p = (char*)malloc(size) + size;
__asm__("movl %0, %%esp\n" :: "r"(p) );

*/

/******** program ********************/

const int MAXN = 1005;

struct node{
    int x,y,step;
    node(){}
    node(int _x,int _y,int _step):x(_x),y(_y),step(_step){}
};

string s[MAXN];
int use[MAXN][MAXN];
int n,m;

int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};

int bfs(){
    queue<node> q;
    int sx = 0,sy = 0;
    memset(use,-1,sizeof(use));
    rep(i,n){
        rep(j,m){
            if(s[i][j]=='E'){
                q.push( node(i,j,0) );
                use[i][j] = 0;
            }
            else if(s[i][j]=='S')
                sx = i , sy = j;
        }
    }

    while(!q.empty()){
        node pre = q.front();
        q.pop();
        rep(d,4){
            int x = pre.x+dx[d];
            int y = pre.y+dy[d];
            if(x<0||y<0||x>=n||y>=m||s[x][y]=='T')
                continue;
            if(~use[x][y])continue;
            use[x][y] = pre.step+1;
            q.push( node(x,y,pre.step+1) );
        }
    }

    int ans = 0;
    rep(i,n)
    rep(j,m)
    if(~use[i][j]&&isdigit(s[i][j])&&use[i][j]<=use[sx][sy])
        ans += s[i][j]-'0';
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m){
        rep(i,n)
            cin>>s[i];
        cout<<bfs()<<endl;
    }

	return 0;
}
