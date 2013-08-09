/*

s^r = p，求最大的r值

分析：
	分析可知：
	例如串
	abcabcabc
	枚举s的长度，当且仅当len%|s|==0时才用考虑。
	这时，第1位与第4位的公共长度为|s|，第1位与第7位的公共长度为|s|*2
	于是可以使用rmq求出两位的最长公共子串长度。
	由于数据范围比较大，所以不能直接使用rmq求。由于每次求得都是与位置1的最长公共子串长度，
	所以可以修改一下rmq的代码。
	
	另外，我们可以注意到s^k与s^(k+1)刚好为suffix(i)与suffix(i+1)的关系，于是又可以直接O(1)判断

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

#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)

const int MAXN = 1000005;

char s[MAXN];
int wa[MAXN],wb[MAXN],wx[MAXN],wy[MAXN];
int r[MAXN],sa[MAXN],Height[MAXN],Rank[MAXN];

int rmq[MAXN];

int c0(int *r,int a,int b){
	return r[a]==r[b]&&r[a+1]==r[b+1]&&r[a+2]==r[b+2];
}

int c12(int k,int *r,int a,int b){
	if(k==2)
		return r[a]<r[b] || ( r[a]==r[b]&&c12(1,r,a+1,b+1) );
	else
		return r[a]<r[b] || ( r[a]==r[b]&&wx[a+1]<wx[b+1] );
}

void sort(int *r,int *a,int *b,int n,int m){
     rep(i,n)
        wx[i] = r[a[i]];
     rep(i,m)
        wy[i]=0;
     rep(i,n)
        wy[wx[i]]++;
     rep1(i,m-1)
        wy[i] += wy[i-1];
     for(int i=n-1;i>=0;i--)
        b[--wy[wx[i]]] = a[i];
}

void dc3(int *r,int *sa,int n,int m){
    int *rn = r+n;
    int *san = sa+n;
    int ta = 0;
    int tb = (n+1)/3;
    int tbc = 0;

    r[n] = r[n+1]=0;

    rep(i,n)
        if(i%3!=0)
            wa[tbc++] = i;

    sort(r+2,wa,wb,tbc,m);
    sort(r+1,wb,wa,tbc,m);
    sort(r,wa,wb,tbc,m);

    int p = 1;
    rn[F(wb[0])] = 0;
    for(int i=1;i<tbc;i++)
        rn[F(wb[i])] = c0(r,wb[i-1],wb[i])?p-1:p++;

    if(p<tbc)
        dc3(rn,san,tbc,p);
    else
        for(int i=0;i<tbc;i++)
            san[rn[i]] = i;

    rep(i,tbc)
        if(san[i]<tb)
            wb[ta++]=san[i]*3;

    if(n%3==1)
        wb[ta++]=n-1;

    sort(r,wb,wa,ta,m);

    rep(i,tbc)
        wx[ wb[i] = G(san[i]) ] = i;

    int i = 0 , j = 0;
    p = 0;
    for(;i<ta && j<tbc;p++)
        sa[p] = c12(wb[j]%3,r,wa[i],wb[j])?wa[i++]:wb[j++];

    for(;i<ta;p++)
        sa[p] = wa[i++];
    for(;j<tbc;p++)
        sa[p] = wb[j++];
}

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
    int t = Rank[0];
    int tmp = len-sa[t];

    for(int i=t;i;i--){
        rmq[i] = tmp;
        tmp = min(tmp,Height[i]);
    }

    tmp = len;
    for(int i=t+1;i<=len;i++){
        tmp = min(tmp,Height[i]);
        rmq[i] = tmp;
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    while(scanf("%s",s),s[0]!='.'){
        int len = strlen(s);
        rep(i,len)
            r[i] = s[i];
        r[len] = 0;

        dc3(r,sa,len+1,128);
        calHeight(r,sa,len);

        initRmq(len);

        int ans = len;
        rep1(i,len){
            if(len%i)continue;
            if(rmq[ Rank[i] ]==len-i){
                ans = i;
                break;
            }
        }
        cout<<len/ans<<endl;
    }

	return 0;
}
