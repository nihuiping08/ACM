/*

題目:
    給出m個木材，現在需要鋸n根木棍，問最多能夠鋸多少根木棍
分析：
    dfs加剪枝。
    我們先對木材以及木棍排序。
    然後二分判斷答案。
    剪枝：
    1.排序
    2.如果前後搜索兩根木棍長度相同的話，則直接從當前的木材往下枚舉（顯
    然前面的都不能夠滿足它）。
    3.如果剩餘的木材總長度不能夠鋸剩餘的木棍，剪枝

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

/******** program ********************/

const int MAXN = 1005;

int a[MAXN],b[MAXN],tmp[MAXN],n,m,mid;
int s[MAXN],waste,sum;

bool dfs(int now,int pos){
    if(now==0)
        return true;

    if(waste>sum-s[mid])
        return false;

    for(int i=pos;i<=m;i++){
        if(a[i]>=b[now]){
            a[i] -= b[now];

            if(a[i]<b[1])
                waste += a[i];

            if(b[now-1]==b[now]){
                if(dfs(now-1,i))
                    return true;
            }else if(dfs(now-1,1))
                return true;

            if(a[i]<b[1])
                waste -= a[i];

            a[i] += b[now];
        }
    }
    return false;
}

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    RD(m);
    rep1(i,m){
        RD(tmp[i]);
        sum += tmp[i];
    }

    RD(n);
    rep1(i,n)
        RD(b[i]);

    sort(tmp+1,tmp+m+1);
    sort(b+1,b+n+1);

    rep1(i,n)
        s[i] = s[i-1]+b[i];

    int l = 1,r = n,ans = 0;
    while(l<=r){
        mid = (l+r)>>1;
        waste = 0;
        rep1(i,m)
            a[i] = tmp[i];
        if(dfs(mid,1)){
            ans = mid;
            l = mid+1;
        }else
            r = mid-1;
    }
    cout<<ans<<endl;

    return 0;
}
