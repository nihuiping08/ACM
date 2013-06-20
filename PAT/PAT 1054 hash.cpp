/*

题目：
	hash，map都可

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

const int MOD = 1000007;

int num[MOD];
int po[MOD],tol;

struct node{
    int val;
    int id;
    int next;
}edge[MOD];

int has(int val){
    int x = val%MOD;
    for(int i=po[x];i;i=edge[i].next)
        if(edge[i].val==val)
            return edge[i].id;
    return -1;
}

int add(int val){
    int x = has(val);
    if(x!=-1)
        return x;

    x = val%MOD;
    ++ tol;
    edge[tol].id = tol;
    edge[tol].val = val;
    edge[tol].next = po[x];
    po[x] = tol;

    return tol;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int val,n,m;
    memset(num,0,sizeof(num));
    memset(po,0,sizeof(po));
    tol = 0;

    int ans = -1;
    RD2(n,m);
    int half = (n*m+1)/2;

    rep(i,n)
        rep(j,m){
            RD(val);
            int x = add(val);
            num[x] ++;
            if(num[x]>=half)
                ans = val;
        }

    printf("%d\n",ans);

	return 0;
}
