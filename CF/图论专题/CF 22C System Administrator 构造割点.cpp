/*

题目：构造点v是连通图的割点
分析：当边数<顶点数-1或者>(n-1)*(n-2)/2时无解
否则，我们可以分成
1.v = 1时，把n-1-2-...-(n-1)，然后右边的1-...-(n-1的边可以随意构造直到
够了为止
2.v != 1时，1-v-2-...-n(可能中间某个顶点为v)，然后从2-n的边随意构造就行了

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

int n,m,v;

void v_1(){
    printf("%d %d\n",n,1);
    for(int i=2;i<n;i++)
        printf("%d %d\n",i,i-1);
    m -= n-1;
    if(m==0)
        return;

    for(int i=1;i<n;i++)
        for(int j=i+2;j<n;j++){
            printf("%d %d\n",i,j);
            if(--m==0)
                return;
        }
}

void v_n(){
    printf("%d %d\n",1,n);
    for(int i=3;i<=n;i++)
        printf("%d %d\n",i,i-1);
    m -= n-1;
    if(m==0)
        return;
    for(int i=2;i<=n;i++)
        for(int j=i+2;j<=n;j++){
            printf("%d %d\n",i,j);
            if(--m==0)
                return;
        }
}

void v_v(){
    printf("%d %d\n",1,v);
    for(int i=3;i<=n;i++)
        printf("%d %d\n",i,i-1);
    m -= n-1;
    if(m==0)
        return;
    for(int i=2;i<=n;i++)
        for(int j=i+2;j<=n;j++){
            printf("%d %d\n",i,j);
            if(--m==0)
                return;
        }
}


int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    bool ok = false;
    while(cin>>n>>m>>v){
        ok?puts("---------------------------"):ok = 1;
        if(m<n-1){
            puts("-1");
            continue;
        }
        ll tmp = ll(n-1)*(n-2)/2+1;
        if(m>tmp){
            puts("-1");
            continue;
        }

        if(v==1)
            v_1();
        else if(v==n)
            v_n();
        else
            v_v();
    }

	return 0;
}
