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

const int MAXN = 1000005;

int fa[MAXN];

struct node{
    int x,y;
}p[MAXN];

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

    int n,m,k,x,y;

    RD3(n,m,k);

    rep(i,m)
        RD2(p[i].x,p[i].y);

    int now;
    while(k--){
        RD(now);
        rep1(i,n)
            fa[i] = i;
        rep(i,m){
            x = find_set(p[i].x);
            y = find_set(p[i].y);
            if(x!=y&&x!=now&&y!=now)
                fa[x] = y;
        }
        int cnt = 0;
        rep1(i,n)
            cnt += fa[i]==i;
        cnt --;
        printf("%d\n",cnt-1);
    }

	return 0;
}
