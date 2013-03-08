/*

题目：lucky数是指数字只有4和7的数，现在给出一棵带有边权的树，问有多少个
三元组(i,j,k),要从 i到j 和 i到k的路径上至少有一条边边权为lucky数
分析：并查集，我们可以对于不是lucky数的边放在一个集合里面，在不同的集合
中必有一条是lucky边权的边连接，所以我们可以通过集合大小统计出答案。

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

const int MAXN = 1e5+5;

int fa[MAXN];
int sz[MAXN];
int n;

int find_set(int x){
    if(fa[x]!=x)
        fa[x] = find_set(fa[x]);
    return fa[x];
}

void union_set(int x,int y){
    x = find_set(x);
    y = find_set(y);
    if(x==y)
        return;
    if(sz[x]>=sz[y]){
        fa[y] = x;
        sz[x] += sz[y];
    }else{
        fa[x] = y;
        sz[y] += sz[x];
    }
}

bool lucky(int x){
    while(x){
        if( x%10!=4 && x%10!=7 )
            return false;
        x /= 10;
    }
    return true;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int x,y,c;
    RD(n);
    for(int i=1;i<=n;i++){
        fa[i] = i;
        sz[i] = 1;
    }
    for(int i=1;i<n;i++){
        RD3(x,y,c);
        if(lucky(c)==false)
            union_set(x,y);
    }
    ll ans = 0;
    for(int i=1;i<=n;i++){
        ll tmp = n-sz[ find_set(i) ];
        ans += tmp*(tmp-1);
    }
    cout<<ans<<endl;

	return 0;
}
