/*

题目：判断二分图
分析：dfs染色

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

/******** program ********************/

const int MAXN = 205;

bool a[MAXN][MAXN];
int col[MAXN],n,m;
vector<int> vec;

bool dfs(int x,int c){
    col[x] = c;
    if(c==1)
        vec.pb(x);

    rep1(y,n){
        if(a[x][y]){
            if(!col[y]&&dfs(y,-c)==false)
                return false;
            else if(col[y]==c)
                return false;
        }
    }
    return true;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n>>m){
        memset(a,false,sizeof(a));
        int x,y;
        while(m--){
            RD2(x,y);
            a[x][y] = a[y][x] = true;
        }
        memset(col,0,sizeof(col));
        vec.clear();

        bool ok = true;
        rep1(i,n)
            if(!col[i])
                ok = dfs(i,1)&&ok;

        if(ok){
            puts("yes");
            cout<<vec.size()<<endl<<vec[0];
            int len = vec.size()-1;
            rep1(i,len)
                printf(" %d",vec[i]);
            puts("");
        }else
            puts("no");
    }

	return 0;
}
