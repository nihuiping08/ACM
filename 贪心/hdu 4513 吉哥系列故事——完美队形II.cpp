/*

分析：把連續相同的數合併之後，暴力向兩邊擴展。需要判斷兩邊的size是否相等
正解：擴展KMP。。

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
#define REP(i,a,b) for(int i=a;i<b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD(n) scanf("%d",&n)
#define RD2(x,y) scanf("%d%d",&x,&y)
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define RD4(x,y,z,w) scanf("%d%d%d%d",&x,&y,&z,&w)

const int MAXN = 100005;

int a[MAXN],n,m;
int sz[MAXN];

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    while(ncase--){
        RD(m);
        memset(sz,0,sizeof(sz));

        int ans = 1;
        int pre = -2000000000;
        int x;
        n = 0;

        rep1(j,m){
            RD(x);
            if(x==pre){
                sz[n] ++;
                ans = max(sz[n],ans);
                pre = a[n];
            }else{
                pre = a[++n] = x;
                sz[n] ++;
            }
        }

        rep1(i,n)
            sz[i] += sz[i-1];

        for(int i=1;i<=n;i++){

            int l = i-1 , r = i;
            int pre = a[i];
            bool ok = true;
            while( l&&r<=n && a[l]<=pre && a[l]==a[r]){
                if(sz[l]-sz[l-1]!=sz[r]-sz[r-1]){
                    //cout<<sz[r-1]<<" "<<sz[l]<<endl;
                    ok = false;
                    //cout<<"ans = "<<ans<<endl;
                    ans = max(ans,sz[r-1]-sz[l]+2*min(sz[l]-sz[l-1],sz[r]-sz[r-1]));
                    //cout<<"ans = "<<ans<<endl;
                    break;
                }
                pre = a[l];
                l --;
                r ++;
            }
            if(ok)
                ans = max(ans,sz[r-1]-sz[l]);

            if(sz[i]-sz[i-1]==1)
                pre = 2000000000;
            else
                pre = a[i];

            l = i-1;
            r = i+1;
            ok = true;
            while( l&&r<=n && a[l]<=pre && a[l]==a[r]){
                if(sz[l]-sz[l-1]!=sz[r]-sz[r-1]){
                    //cout<<sz[r-1]<<" "<<sz[l]<<endl;
                    ok = false;
                    //cout<<"ans = "<<ans<<endl;
                    ans = max(ans,sz[r-1]-sz[l]+2*min(sz[l]-sz[l-1],sz[r]-sz[r-1]));
                    //cout<<"ans = "<<ans<<endl;
                    break;
                }
                pre = a[l];
                l --;
                r ++;
            }
            if(ok)
                ans = max(ans,sz[r-1]-sz[l]);
        }
        printf("%d\n",ans);
    }

    return 0;
}
