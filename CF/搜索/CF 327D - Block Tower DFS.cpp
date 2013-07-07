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

/******** program ********************/

const int MAXN = 505;

char s[MAXN][MAXN];
int n,m;
bool use[MAXN][MAXN];

struct node{
    char op;
    int x,y;
    node(){}
    node(char a,int b,int c):op(a),x(b),y(c){}
};

vector<node> vec;

int dx[] = {0,0,-1,1};
int dy[] = {1,-1,0,0};

bool out(int x,int y){
    return x<1||y<1||x>n||y>m;
}

void dfs(int x,int y,bool has){
    use[x][y] = true;

    bool ok = false;
    rep(i,4){
        int cx = dx[i]+x;
        int cy = dy[i]+y;
        if(!out(cx,cy)&&!use[cx][cy]&&s[cx][cy]=='.')
            ok = true;
    }

    if(!ok&&has){
        vec.pb( node('R',x,y) );
        return;
    }


    vec.pb( node('B',x,y) );
    rep(i,4){
        int cx = dx[i]+x;
        int cy = dy[i]+y;
        if( !out(cx,cy) && !use[cx][cy] && s[cx][cy]=='.'){
            dfs(cx,cy,true);
            ok = true;
        }
    }

    if(has){
        vec.pb( node('D',x,y) );
        vec.pb( node('R',x,y) );
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase = false;
    while(cin>>n>>m){
        vec.clear();
        ncase?puts(""):ncase = true;
        memset(use,false,sizeof(use));
        rep1(i,n)
            scanf("%s",s[i]+1);

        rep1(i,n)
            rep1(j,m)
                if(s[i][j]=='.' && !use[i][j])
                    dfs(i,j,false);
        cout<<vec.size()<<endl;
        foreach(i,vec)
            printf("%c %d %d\n",vec[i].op,vec[i].x,vec[i].y);
    }

	return 0;
}
