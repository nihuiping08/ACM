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

const int MAXN = 2e5+5;

char s[MAXN];

int pre[MAXN],next[MAXN];

void del(int x,int y){
    next[ pre[x] ] = next[y];
    pre[ next[y] ] = pre[x];
}

void ins(int x,int y){
    pre[y] = x;
    next[x] = y;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~scanf("%s",s+1)){
        int n = strlen(s+1);
        rep(i,n+1)
            ins(i,i+1);
        for(int x=next[0];next[x]<=n;){
            int y = next[x];
            if(s[x]==s[y]){
                int t = pre[x];
                del(x,y);
                x = t;
            }else
                x=next[x];
        }
        for(int i=next[0];i<=n;i=next[i])
            printf("%c",s[i]);
        puts("");
    }

	return 0;
}
