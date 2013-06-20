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

const int MAXN = 1005;

double ex[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int k , x;
    double e;

    memset(ex,0,sizeof(ex));

    scanf("%d",&k);
    while(k--){
        scanf("%d%lf",&x,&e);
        ex[x] += e;
    }

    scanf("%d",&k);
    while(k--){
        scanf("%d%lf",&x,&e);
        ex[x] += e;
    }

    int cnt = 0;
    for(int i=MAXN-1;i>=0;i--) // 指数居然有负数。。。
        cnt += (ex[i]!=0);

    cout<<cnt;
    for(int i=MAXN-1;i>=0;i--)
        if(ex[i])
            printf(" %d %.1lf",i,ex[i]);
    puts("");

	return 0;
}
