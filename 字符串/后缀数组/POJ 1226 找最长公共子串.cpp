/*

题目：找出n个串的最长公共子串（一个串可以翻转过来）
分析：后缀数组，二分答案，然后根据height数组分组，一个组里面全部height>=mid，然后判断该组里是否
全部串都存在。

*/
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
#define cmax(x,y) x = max(x,y)
#define cmin(x,y) x = min(x,y)
#define Clear(x) memset(x,0,sizeof(x))
//#pragma comment(linker, "/STACK:1024000000,1024000000")

/******** program ********************/
const int MAXN = 1e5+5;

char s[MAXN];
int wa[MAXN],wb[MAXN],wx[MAXN],wy[MAXN];
int r[MAXN],sa[MAXN],Height[MAXN],Rank[MAXN];
bool use[105];
int loc[MAXN];

bool cmp(int *r,int a,int b,int d){
    return r[a]==r[b]&&r[a+d]==r[b+d];
}

void da(int *r,int *sa,int n,int m){
    int *x = wa , *y = wb;

    // 基数排序
    rep(i,m)
        wx[i] = 0;
    rep(i,n)
        wx[ x[i] = r[i] ] ++;
    rep1(i,m-1)
        wx[i] += wx[i-1];
    for(int i=n-1;i>=0;i--)
        sa[ --wx[x[i]] ] = i;

    int p = 1;
    for(int j = 1;p<n;j<<=1,m=p){
        // 第二关键字排序
        p = 0;
        for(int i=n-j;i<n;i++)
            y[p++] = i;
        rep(i,n)
            if(sa[i]>=j)
                y[p++] = sa[i]-j;

        // 第一关键字排序
        rep(i,n)
            wy[i] = x[y[i]];
        rep(i,m)
            wx[i] = 0;
        rep(i,n)
            wx[ wy[i] ] ++;
        rep1(i,m-1)
            wx[i] += wx[i-1];
        for(int i=n-1;i>=0;i--)
            sa[ --wx[ wy[i] ] ] = y[i];

        swap(x,y);
        p = 1;
        x[sa[0]] = 0;
        rep1(i,n-1)
            x[sa[i]] = cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
}

void calHeight(int *r,int *sa,int n){
    rep1(i,n)
        Rank[sa[i]] = i;
    for(int i=0,k=0,j;i<n;Height[Rank[i++]]=k)
        for(k?k--:0,j=sa[Rank[i]-1];r[i+k]==r[j+k];k++);
}

bool ok(int mid,int len,int n){
    int j = 0;
    for(int i=1;i<=len;i=j+1){
        for(;i<=len&&Height[i]<mid;i++);
        for(j=i;j<=len&&Height[j]>=mid;j++);
        if(j-i+1<n)continue;

        Clear(use);
        int ans = 0;
        for(int k=i-1;k<j;k++){
            if(loc[sa[k]]&&!use[ loc[sa[k]] ]){
                use[ loc[sa[k]] ] = true;
                ans ++;
            }
        }
        if(ans>=n)return true;
    }
    return false;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    while(ncase--){
        int n;
        int len = 0;

        RD(n);
        rep1(i,n){
            scanf("%s",s);
            int k = strlen(s);
            rep(j,k){
                r[len] = 200+(int)s[j];
                loc[len++] = i;
            }
            r[len] = i*2-1;
            loc[len++] = 0;

            reverse(s,s+k);
            rep(j,k){
                r[len] = 200+(int)s[j];
                loc[len++] = i;
            }
            r[len] = i*2;
            loc[len++] = 0;
        }
        r[--len] = 0;

        if(n==1){
            cout<<strlen(s)<<endl;
            continue;
        }

        da(r,sa,len+1,400);
        calHeight(r,sa,len);

        int ans = 0;
        int l = 1 , r = 100;
        while(l<=r){
            int mid = (l+r)>>1;
            if(ok(mid,len,n)){
                ans = mid;
                l = mid+1;
            }else
                r = mid-1;
        }
        cout<<ans<<endl;
    }

	return 0;
}
