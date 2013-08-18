/*

题意：树上的最长路径
解法：treedp，或者两次DFS

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

vector< PII > adj[MAXN];

int MAX , nx;
void dfs(int x,int fa,int sum){
    if(sum>MAX){
        MAX = sum;
        nx = x;
    }
    foreach(i,adj[x]){
        int y = adj[x][i].first;
        if(y==fa)continue;
        dfs(y,x,sum+adj[x][i].second);
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,m;
    int x,y,z;
    char op[2];
    while(cin>>n>>m){
        rep1(i,n)
            adj[i].clear();
        while(m--){
            RD3(x,y,z);
            scanf("%s",op);
            adj[x].pb( MP(y,z) );
            adj[y].pb( MP(x,z) );
        }
        MAX = 0;
        dfs(1,0,0);
        int tmp = nx;
        MAX = 0;
        dfs(tmp,0,0);
        cout<<MAX<<endl;
    }

	return 0;
}
