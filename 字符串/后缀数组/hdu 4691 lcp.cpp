/*

题目：按照压缩串的格式，给出压缩之后的长度。
分析：直接求一次sa，然后求相邻的lcp计算即可

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
#include <utility>
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
/*

#pragma comment(linker, "/STACK:1024000000,1024000000")

int size = 256 << 20; // 256MB
char *p = (char*)malloc(size) + size;
__asm__("movl %0, %%esp\n" :: "r"(p) );

*/

/******** program ********************/


#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)

const int MAXN = 500005;

char s[MAXN];
int wa[MAXN],wb[MAXN],wx[MAXN],wy[MAXN];
int r[MAXN],sa[MAXN],Height[MAXN],Rank[MAXN];

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


int Log[MAXN];
int best[20][MAXN];
void initRMQ(int n) {//初始化RMQ
    for(int i = 1; i <= n ; i ++) best[0][i] = Height[i];
    for(int i = 1; i <= Log[n] ; i ++) {
        int limit = n - (1<<i) + 1;
        for(int j = 1; j <= limit ; j ++) {
            best[i][j] = min(best[i-1][j] , best[i-1][j+(1<<i>>1)]);
        }
    }
}
void init(){
	Log[0] = -1;
    for(int i=1;i<=MAXN;i++)
        Log[i]=(i&(i-1))?Log[i-1]:Log[i-1] + 1 ;
}
int lcp(int a,int b) {//询问a,b后缀的最长公共前缀
    a = Rank[a];    b = Rank[b];
    if(a > b) swap(a,b);
    a ++;
    int t = Log[b - a + 1];
    return min(best[t][a] , best[t][b - (1<<t) + 1]);
}


struct node{
    int x,y,next;
}edge[MAXN];

struct P{
    int x,y;
}p[MAXN];

int cc(int x){
    if(x==0)return 1;
    int ans = 0;
    while(x>0){
        ans ++;
        x /= 10;
    }
    return ans;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif


	init();

    while(~scanf("%s",s)){
        int len = strlen(s);
        rep(i,len)
            r[i] = s[i];
        r[len] = 0;

        dc3(r,sa,len+1,130);
        calHeight(r,sa,len);
        initRMQ(len);

        //cout<<"-------------- "<<lcp(12,12)<<endl;

        /*
        rep(i,len)
            cout<<Rank[i]<<" ";
        cout<<endl;
        */

        int n;
        RD(n);
        ll ret = 0;
        rep1(i,n){
            scanf("%d%d",&p[i].x,&p[i].y);
            ret += p[i].y-p[i].x+1;
        }

        ll ans = 0;

        ans = p[1].y-p[1].x+3;

        for(int i=2;i<=n;i++){
            if(p[i-1].x==p[i].x){
                int b = min(p[i-1].y-p[i-1].x,p[i].y-p[i].x);
                //cout<<ans<<endl;
                ans += 2+cc(b)+ (p[i].y-p[i].x-b);
                //cout<<"len = "<<b<<endl;
            }else{
                int a = lcp( p[i-1].x , p[i].x );
                //cout<<"len = "<<a<<endl;
                int b = min( p[i-1].y-p[i-1].x , p[i].y-p[i].x );
                a = min(a,b);
                //cout<<"*len = "<<a<<endl;
                ans += 2+cc(a)+p[i].y-p[i].x-a;
            }
        }

        printf("%I64d %I64d\n",ret,ans);
    }

	return 0;
}
