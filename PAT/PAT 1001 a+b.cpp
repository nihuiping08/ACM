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


int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int a,b;

    while(~RD2(a,b)){
        a += b;
        if(a==0){ // 特殊
            puts("0");
            continue;
        }
        if(a<0)
            printf("-");

        int t[10] , top = 0;
        a = max(a,-a);
        while(a){
            t[top++] = a%1000;
            a /= 1000;
        }
        for(int i=top-1;i>=0;i--){
            if(i!=top-1)
                printf(",%03d",t[i]); // 格式控制
            else
                printf("%d",t[i]);
        }
        puts("");
    }

	return 0;
}
