/*

题目：给出n-1条边，每天会有一条边需删掉，然后每天补上一条新的边，问
最少需要多少天，使得这n个点互相连通。
分析：并查集。若存在环，需要把它删掉。然后对于不相交的集合需要补上边

*/
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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

const int MAXN = 1005;

int fa[MAXN],n;

int find_set(int x){
    if(fa[x]!=x)
        fa[x] = find_set(fa[x]);
    return fa[x];
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(cin>>n){
        vector< pair<int,int> > vec;
        for(int i=1;i<=n;i++)
            fa[i] = i;

        int x,y;
        for(int i=1;i<n;i++){
            RD2(x,y);
            int px = find_set(x);
            int py = find_set(y);
            if(px!=py)
                fa[py] = px;
            else
                vec.pb( make_pair(x,y) );
        }
        vector<int> ans;
        for(int i=1;i<=n;i++)
            if(find_set(i)==i)
                ans.pb(i);

        int len = vec.size();
        cout<<len<<endl;
        for(int i=1;i<=len;i++)
            cout<<vec[i-1].first<<" "<<vec[i-1].second<<" "<<ans[i-1]<<" "<<ans[i]<<endl;

    }

	return 0;
}
