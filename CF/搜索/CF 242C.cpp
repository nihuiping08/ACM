/*

无节操搜索题。。。

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
#define fir first
#define sec second
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/

const int MAXN = 1e5+5;

map<PII,int> ma;
set<PII> s;
queue<PII> q;
vector<bool> use;
int sx,sy,ex,ey,n;

int dx[] = {-1,-1,-1,0,0,1,1,1};
int dy[] = {-1,0,1,-1,1,-1,0,1};

int solve(){
    q.push( MP(sx,sy) );
    ma[ MP(sx,sy) ] = 1;

    while(!q.empty()){
        PII p = q.front();
        q.pop();
        int px = p.first;
        int py = p.second;
        int step = ma[MP(px,py)];
        if(px==ex&&py==ey)return step-1;
        rep(i,8){
            int x = px+dx[i];
            int y = py+dy[i];
            if(s.find(MP(x,y))==s.end())
                continue;
            if( ma[MP(x,y)] )continue;
            ma[ MP(x,y) ] = step+1;
            q.push( MP(x,y) );
        }
    }
    return -1;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(RD4(sx,sy,ex,ey)!=EOF){
        RD(n);
        s.clear();
        ma.clear();
        while(q.size())
            q.pop();

        int x,l,r;
        while(n--){
            RD3(x,l,r);
            REP(y,l,r)
                s.insert( MP(x,y) );
        }
        cout<<solve()<<endl;
    }

	return 0;
}
