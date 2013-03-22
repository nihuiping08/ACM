/*

题目：若有环，输出"YES"，否则输出最大的联通块的长度
分析：并查集+sz数组

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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

const int MAXN = 100005;

int fa[MAXN],sz[MAXN];

int find_set(int x){
    if(x!=fa[x]){
        sz[x] += sz[fa[x]];
        fa[x] = find_set(fa[x]);
    }
    return fa[x];
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int n,m;
    while(~RD2(n,m)){
        int x,y,z;
        memset(sz,0,sizeof(sz));
        rep1(i,n)
            fa[i] = i;
        bool ok = false;
        while(m--){
            RD3(x,y,z);
            if(ok)
                continue;
            int px = find_set(x);
            int py = find_set(y);
            if(px==py)
                ok = true;
            else{
                fa[px] = py;
                sz[py] += sz[px]+z;
            }
        }
        if(ok){
            puts("YES");
            continue;
        }
        int ans = 0;
        rep1(i,n)
            ans = max(ans,sz[find_set(i)]);
        cout<<ans<<endl;
    }

	return 0;
}
