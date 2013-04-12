/*

分析：先對每個流行著落點進行bfs，最後對人進行bfs。。。

*/
#include <queue>
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

const int MAXN = 310;

int t[MAXN][MAXN],n;
bool use[MAXN][MAXN];

struct node{
    int x,y,t;
    node(){}
    node(int _x,int _y,int _t):x(_x),y(_y),t(_t){}
};

queue<node> q;
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};

void init(){
    memset(t,-1,sizeof(t));
    int ncase;
    RD(ncase);
    int x,y,z;
    while(ncase--){
        RD3(x,y,z);
        if( t[x][y]==-1 || t[x][y]>z )
            t[x][y] = z;
        rep(i,4){
            int cx = x+dx[i];
            int cy = y+dy[i];
            if(cx<0||cx>n||cy<0||cy>n)
                continue;
            if(t[cx][cy]==-1||t[cx][cy]>z)
                t[cx][cy] = z;
        }
    }
}

int bfs(){
    if(t[0][0]==0)
        return -1;
    if(t[0][0]==-1)
        return 0;
    q.push(node(0,0,0));
    use[0][0] = true;

    while(q.size()){
        node p = q.front();
        q.pop();

        if(t[p.x][p.y]==-1)
            return p.t;
        if(t[p.x][p.y]<=p.t)
            continue;

        p.t ++;
        rep(i,4){
            int x = p.x+dx[i];
            int y = p.y+dy[i];
            if(x<0||y<0||x>n||y>n||use[x][y])
                continue;
            use[x][y] = true;
            if(t[x][y]==-1||t[x][y]>p.t){
                if(t[x][y]==-1)
                    return p.t;
                q.push( node(x,y,p.t) );
            }
        }
    }
    return -1;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    n = 305; // bug
    init();
    cout<<bfs()<<endl;

	return 0;
}
