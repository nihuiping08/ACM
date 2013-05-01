/*

題目：2 4 3 4 2，n個數，每個數表示樓的高度，如果高度為0，表示沒有樓房。問最少一共有多少個樓房
分析：單調棧。

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

#define lx(x) (x<<1)
#define rx(x) (x<<1|1)
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

/******** program ********************/

const int MAXN = 1e5+5;

int a[MAXN],n;
map<int,int> ma;
int q[MAXN];

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase = 0;
    while(cin>>n){
        printf("Case %d: ",++ncase);
        rep1(i,n)
            RD(a[i]);

        ma.clear();
        int ans = 0;
        int top = 0;

        rep1(i,n){
            if( a[i]==0 ){
                ma.clear();
                top = 0;
                continue;
            }

            while( top&&a[ q[top] ]>=a[i] )
                top --;

            int x = a[i];
            if(top){
                if( ma[x]<ma[ a[q[top]] ] )
                    ans ++;
            }else if(ma[x]==0)
                ans ++;

            ma[ x ] = i;
            q[++top] = i;
        }
        cout<<ans<<endl;
    }

	return 0;
}
