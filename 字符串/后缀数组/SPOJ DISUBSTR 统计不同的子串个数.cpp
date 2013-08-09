/*

统计一个字符串中拥有多少个不同的子串

直接根据height数组统计，第i个的前height_i跟其他的有重复，所以可以直接根据len-sa_i-height_i来计算

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



int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    int ncase;
    RD(ncase);
    while(ncase--){
        scanf("%s",s);
        int len = strlen(s);
        rep(i,len)
            r[i] = s[i];
        r[len] = 0;

        da(r,sa,len+1,130);
        calHeight(r,sa,len);

        int ans = 0;
        REP(i,1,len)
            ans += len-sa[i]-Height[i];
        printf("%d\n",ans);
    }

	return 0;
}
