#include <queue>
#include <cmath>
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

const int MAXN = 200005;
const int MAXM = 505;

bool use[MAXN];
bool vis[MAXM][MAXM];
int map[MAXM][MAXM];

int dx[] = {1,0,-1,0};
int dy[] = {0,1,0,-1};

struct node{
    int x,y,s;
    node(){}
    node(int _x,int _y):x(_x),y(_y){s = 0;}
    node(int _x,int _y,int _s):x(_x),y(_y),s(_s){}

    void out(){
        cout<<x<<" "<<y<<endl;
    }
}pa[MAXN];

void check(){
    for(int i=0;i<101;i++){
        for(int j=0;j<101;j++)
            cout<<map[i][j]<<" ";
        cout<<endl;
    }
    puts("");
}

void init(){
    use[1] = true;
    for(int i=2;i<MAXN;i++)
        if(!use[i])
            for(int j=i+i;j<MAXN;j+=i)
                use[j] = true;

    int dx = 200 , dy = 200;
    int now = 3;
    map[dx][dy] = 1;
    pa[1] = node(dx,dy);

    for(int q=0;q<200;q++){
        int id = now*now;
        now += 2;
        int len = q*2+3;
        dx ++;
        dy ++;

        map[dx][dy] = id;
        pa[id] = node(dx,dy);

        int x = dx,y = dy;

        while( dy-y+1<len ){
            y --;
            map[x][y] = map[x][y+1]-1;
            pa[ map[x][y] ] = node(x,y);
        }
        while( dx-x+1<len ){
            x --;
            map[x][y] = map[x+1][y]-1;
            pa[ map[x][y] ] = node(x,y);
        }
        while( y<dy ){
            ++ y;
            map[x][y] = map[x][y-1]-1;
            pa[ map[x][y] ] = node(x,y);
        }
        while(x<dx-1){
            ++ x;
            map[x][y] = map[x-1][y] -1;
            pa[ map[x][y] ] = node(x,y);
        }
    }
}

void bfs(int n,int m){
    node s = pa[n];
    node t = pa[m];

    memset(vis,false,sizeof(vis));
    queue<node> q;
    q.push( s );
    vis[s.x][s.y] = 1;

    while(q.size()){
        node pre = q.front();
        q.pop();
        if(pre.x==t.x&&pre.y==t.y){
            cout<<pre.s<<endl;
            return;
        }
        rep(i,4){
            int x = pre.x+dx[i];
            int y = pre.y+dy[i];
            if(x<0||y<0||x>400||y>400)
                continue;
            if(vis[x][y])   continue;
            if(use[ map[x][y] ]==false)
                continue;
            vis[x][y] = true;
            q.push( node(x,y,pre.s+1) );
        }
    }
    puts("impossible");
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    init();
    //check();
    int n,m;
    int ncase = 0;
    while(~RD2(n,m)){
        printf("Case %d: ",++ncase);
        bfs(n,m);
    }

	return 0;
}
