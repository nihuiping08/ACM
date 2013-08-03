/*

从一个猜字谜的矩阵中找出模式串的位置，注意可以从八个方向找	ac自动机简单题
处理一下方向之后，就是ac自动机模板题

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

const int MAXN = 1e5+5;
const int kind = 26;

char t[1005];

int dx[] = {-1,-1,0,1,1,1,0,-1};
int dy[] = {0,1,1,1,0,-1,-1,-1};

struct node{
    int x,y;
    char c;
    int len;
    void init(){
        x = -1;
    }
}ans[MAXN];

struct AC{
    int ch[MAXN][kind],fail[MAXN],last[MAXN];
    int ed[MAXN],tot;

    void set(int x){
        Clear(ch[x]);
        ed[x] = last[x] = fail[x] = 0;
    }

    void init(){
        set(0);
        tot = 0;
    }

    int newNode(){
        int x = ++ tot;
        set(x);
        return x;
    }

    int ind(char c){
        return c-'A';
    }

    void insert(char *s,int id){
        int r = 0;
        for(int i=0;s[i];i++){
            int c = ind(s[i]);
            if(ch[r][c]==0)
                ch[r][c] = newNode();
            r = ch[r][c];
        }
        ed[r] = id;
    }

    int has(char *s){
        int r = 0;
        for(int i=0;s[i];i++){
            int c = ind(s[i]);
            if(ch[r][c]==0)
                return 0;
            r = ch[r][c];
        }
        return ed[r];
    }

    void build(){
        queue<int> q;
        rep(c,kind){
            int x = ch[0][c];
            if(x) q.push(x);
        }
        while(!q.empty()){
            int r = q.front();
            q.pop();
            rep(c,kind){
                int x = ch[r][c];
                if(!x){
                    ch[r][c] = ch[ fail[r] ][c];
                    continue;
                }
                q.push(x);
                int y = fail[r];
                while( y && ch[y][c]==0 )
                    y = fail[y];
                fail[x] = ch[y][c];
                last[x] = ed[ fail[x] ]?fail[x]:last[ fail[x] ];
            }
        }
    }

    void run(char *s,int sx,int sy,int d){
        int r = 0;
        for(int i=0;s[i];i++){
            int c = ind(s[i]);
            r = ch[r][c];

            int x = 0;
            if(ed[r])
                x = r;
            else if( last[r] )
                x = last[r];

            while(x){
                if( ed[x] && ans[ed[x]].x==-1 ){
                    int len = ans[ed[x]].len;
                    ans[ed[x]].x = sx+dx[d]*(i+1-len);
                    ans[ed[x]].y = sy+dy[d]*(i+1-len);
                    ans[ed[x]].c = char('A'+d);
                }
                x = last[x];
            }
        }
    }
}ac;

int n,m,q;
char s[1005][1005];

bool out(int x,int y){
    return x<0 || y<0 || x>=n || y>=m;
}

void cc(int d,int x,int y){
    int top = 0;
    int sx = x , sy = y;

    while(!out(x,y)){
        t[top++] = s[x][y];
        x += dx[d];
        y += dy[d];
    }

    t[top] = '\0';

    ac.run(t,sx,sy,d);
}

void solve(){
    // 0 A 上
    rep(j,m)
        cc(0,n-1,j);

    // 1 B 右上
    rep(i,n)
        cc(1,i,0);
    rep1(j,m-1)
        cc(1,n-1,j);

    // 2 C 右
    rep(i,n)
        cc(2,i,0);

    // 3 D 右下
    rep(j,m)
        cc(3,0,j);
    rep1(i,n-1)
        cc(3,i,0);

    // 4 E 下
    rep(j,m)
        cc(4,0,j);

    // 5 F 左下
    rep(j,m)
        cc(5,0,j);
    rep1(i,n-1)
        cc(5,i,m-1);

    // 6 G 左
    rep(i,n)
        cc(6,i,m-1);

    // 7 H 左上
    rep(i,n-1)
        cc(7,i,m-1);
    rep(j,m)
        cc(7,n-1,j);

    rep1(i,q)
        printf("%d %d %c\n",ans[i].x,ans[i].y,ans[i].c);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m>>q){
        rep(i,n)
            scanf("%s",s[i]);

        ac.init();
        rep1(i,q){
            scanf("%s",t);
            ac.insert(t,i);
            ans[i].init();
            ans[i].len = strlen(t);
        }
        ac.build();

        solve();
    }

	return 0;
}
