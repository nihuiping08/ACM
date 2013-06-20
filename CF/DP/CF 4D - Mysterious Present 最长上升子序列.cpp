/*

最长上升子序列

*/
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

const int MAXN = 5005;

int dp[MAXN];
int pre[MAXN];
int n,w,h;

struct node{
    int x,y,id;
    void rd(int i){
        RD2(x,y);
        id = i;
    }
    friend bool operator < (node a,node b){
        return a.x<b.x||(a.x==b.x&&a.y<b.y);
    }
}p[MAXN];

void dfs(int x){
    if(pre[x]!=-1)
        dfs(pre[x]);
    cout<<p[x].id<<" ";
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif


    while(~RD3(n,w,h)){
        rep1(i,n)
            p[i].rd(i);
        sort(p+1,p+n+1);

        memset(dp,0,sizeof(dp));
        memset(pre,-1,sizeof(pre));
        rep1(i,n){
            if(p[i].x<=w||p[i].y<=h)
                continue;
            dp[i] = 1;
            pre[i] = -1;
            rep1(j,i-1){
                if( p[j].x>w&&p[j].y>h && p[j].x<p[i].x&&p[j].y<p[i].y){
                    if( dp[i]<dp[j]+1){
                        dp[i] = dp[j]+1;
                        pre[i] = j;
                    }
                }
            }
        }

        int ans = n;
        rep1(i,n)
            if(dp[i]>dp[ans])
                ans = i;
        cout<<dp[ans]<<endl;
        if(dp[ans]){
            dfs(ans);
            puts("");
        }
    }

	return 0;
}
