/*

題目：
    給出n個數，問中位數為m的連續的子序列的個數
    
分析：
    我們先找出m的位置，然後用+1，-1，+0的方式統計出連續跟m的關係。
    比如
    7 4
    5 7 2  4 3 1 6
    我們可以這樣統計：
    5 7 2  4 3 1 6
    1 0 -1 0
           0 1 2 1
    對於每個數字的絕對值分別統計，然後計數的時候加上左右該絕對值數目
    的乘機（注意乘號）
    
*/
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

/******** program ********************/

const int MAXN = 100005;

int a[MAXN],use[2][MAXN],b[2][MAXN],n,m;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~RD2(n,m)){
        memset(use,0,sizeof(use));
        memset(b,0,sizeof(b));
        int pos = 0;
        rep1(i,n){
            RD(a[i]);
            if(a[i]==m)
                pos = i;
        }

        int tmp = 0;
        a[pos] = 0;
        int n0 = 0,n1 = 0;

        int x = 0;
        for(int i=pos-1;i;i--){
            if(a[i]<m)
                x --;
            else
                x ++;
            tmp = max(tmp,max(x,-x));
            if(x==0)
                n0 ++;
            else if(x>0)
                use[1][x] ++;
            else
                use[0][-x] ++;
        }

        x = 0;
        for(int i=pos+1;i<=n;i++){
            if(a[i]>m)
                x --;
            else
                x ++;
            tmp = max(tmp,max(x,-x));
            if(x==0)
                n1 ++;
            else if(x>0)
                b[1][x] ++;
            else
                b[0][-x] ++;
        }

        ll ans = 1+n0+n1+ll(n0)*n1;
        //cout<<"ans = "<<ans<<endl;
        rep1(i,tmp)
            ans += ll(use[0][i])*b[0][i]+ll(use[1][i])*b[1][i];
        cout<<ans<<endl;
    }
	return 0;
}
