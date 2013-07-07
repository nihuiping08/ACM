/*

题目：寻找最小的且满足有n个因子的数
分析：直接dfs剪枝

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

int n;
ll ans;
int p[] = {2,3,5,7,11,13,17,19,23,29};
int use[100];

void dfs(int id,int res,ll now){
    if(id==10)return;
    if(now>ans)return;
    if(res>n)return;
    if(res==n){
        ans = min(ans,now);
        return;
    }

    dfs( id+1,res,now );

    ll ret = 1;
    rep1(i,60){
        if(ans/now/p[id]<ret)
            break;
        ret *= p[id];
        dfs(id+1,res*(i+1),now*ret);
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD(n)){
        memset(use,0,sizeof(use));

        ans = 1e18;
        dfs(0,1,1);
        cout<<ans<<endl;
    }

	return 0;
}
