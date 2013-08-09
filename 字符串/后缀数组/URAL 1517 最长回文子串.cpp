/*

题目：输出最长的回文子串

分析：后缀数组，连接正串以及该串的反串，分析可以知道：
	回文子串长度为奇数时：abcba@abcba^，第i位作为回文中心时，对应的后半部分为i+cur，前半部分
	对应的起始位置为len-i-1，半径为两者的公共前缀，即两者之间的最小height值，利用rmq可以快速
	求出
	同理：作为偶数时，abba@abba^时，第i位对应第len-i位。

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
const int MAXN = 2e5+5;

char s[MAXN];
int wa[MAXN],wb[MAXN],wx[MAXN],wy[MAXN];
int r[MAXN],sa[MAXN],Height[MAXN],Rank[MAXN];

int rmq[MAXN];
int mm[MAXN];
int best[20][MAXN];

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

void initRmq(int len){
    rep1(i,len)
        rmq[i] = Height[i];
    mm[0] = -1;
    rep1(i,len)
         mm[i] = mm[i-1]+( (i&(i-1))==0 );
    rep1(i,len)
        best[0][i] = i;
    rep1(i,mm[len])
        rep1(j,len+1-(1<<i)){
            int a = best[i-1][j];
            int b = best[i-1][ j+( 1<<(i-1) ) ];
            best[i][j] = rmq[a]<rmq[b]?a:b;
        }
}

int askRmq(int a,int b){
    int t = mm[b-a+1];
    b -= (1<<t)-1;
    a = best[t][a];
    b = best[t][b];
    return rmq[a]<rmq[b]?a:b;
}

int lcp(int a,int b){
    a = Rank[a];
    b = Rank[b];
    if(a>b)swap(a,b);
    return Height[ askRmq(a+1,b) ];
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(~scanf("%s",s)){
        int len = strlen(s);
        int k = len;
        rep(i,k)
            r[i] = s[i];
        r[len] = 1;

        rep(i,k)
            r[len+1+i] = s[len-1-i];
        len = len*2+1;
        r[len] = 0;

        da(r,sa,len+1,130);
        calHeight(r,sa,len);
        initRmq(len);

        int ans = 0;
        int pos = 0;
        rep(i,k){
            // abba@abba^
            int a = lcp(i,len-i); // 偶数长度
            if(ans<a*2){
                ans = a*2;
                pos = i-a;
            }
            // abcba@abcba^
            a = lcp(i,len-i-1); // 奇数长度
            if(ans<a*2-1){
                ans = a*2-1;
                pos = i-a+1;
            }
        }
        s[ ans+pos ] = '\0';
        //cout<<ans<<" ";
        printf("%s\n",s+pos);
    }

	return 0;
}
