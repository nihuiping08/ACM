/*

题目：
    给出一棵树，去掉一个节点之后，可能会变成森林，现在需要使得森林中
    的树的节点数最大的尽可能小。这样的节点成为树的中心。现在问该树有
    多少个树的中心

分析：
    dfs可以求出以该节点为根的子树节点个数。然后算出删掉该节点后儿子节点
    以及他父节点所在的树的节点个数的最大值。
    如果该值最小，答案就是它。
    如果该值跟目前答案一样大，把它放进存中心节点的数组中。

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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 16005;

vector<int> vec[MAXN];
vector<int> a;
int sz[MAXN];
int n,ans;

void dfs(int x,int fa){
    sz[x] = 1;
    int MAX = 0;
    foreach(i,vec[x]){
        int y = vec[x][i];
        if(y==fa)
            continue;
        dfs(y,x);
        MAX = max(sz[y],MAX);
        sz[x] += sz[y];
        //cout<<x<<" "<<y<<endl;
    }
    MAX = max(MAX,n-sz[x]);
    //cout<<x<<" "<<MAX<<endl;
    if(MAX<ans){
        a.clear();
        ans = MAX;
        a.pb(x);
    }else if(MAX==ans)
        a.pb(x);
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int x,y;
    RD(n);
    ans = 1e8;
    rep(i,n-1){
        RD2(x,y);
        vec[x].pb(y);
        vec[y].pb(x);
    }

    dfs(1,0);
    sort(a.begin(),a.end());
    cout<<ans<<" "<<a.size()<<endl;
    foreach(i,a){
        if(i)
            cout<<" ";
        cout<<a[i];
    }
    cout<<endl;
	return 0;
}
