/*

题目：
	给出n个字符串，问最多能够选出多少个串组成序列，并满足前一个字符串是
	后一个字符串的子串。

分析：
　　AC自动机经典水题。。。
　　考虑每个节点结尾时，他能够选出最多的串 
		= max{ 父节点选出  ， fail节点选出 }+以该节点为结尾的单词个数

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
#include <complex>
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
#define lson rt<<1
#define rson rt<<1|1
#define SZ(x) x.size()

/*

#pragma comment(linker, "/STACK:1024000000,1024000000")

int ssize = 256 << 20; // 256MB
char *ppp = (char*)malloc(ssize) + ssize;
__asm__("movl %0, %%esp\n" :: "r"(ppp) );

*/

char IN;
bool NEG;
inline void Int(int &x){
    NEG = 0;
    while(!isdigit(IN=getchar()))
        if(IN=='-')NEG = 1;
    x = IN-'0';
    while(isdigit(IN=getchar()))
        x = x*10+IN-'0';
    if(NEG)x = -x;
}
inline void LL(ll &x){
    NEG = 0;
    while(!isdigit(IN=getchar()))
        if(IN=='-')NEG = 1;
    x = IN-'0';
    while(isdigit(IN=getchar()))
        x = x*10+IN-'0';
    if(NEG)x = -x;
}

/******** program ********************/

const int MAXN = 1e6+5;
const int kind = 26;

char s[MAXN];

struct AC{

    int dp[MAXN];
    int ch[MAXN][kind],fail[MAXN];
    int end[MAXN];
    int tot;

    inline void set(int x){
        Clear(ch[x]);
        fail[x] = end[x] = dp[x] = 0;
    }
    inline void init(){
        set(tot = 1);
    }
    inline int newNode(){
        set(++tot);
        return tot;
    }
    inline int ind(char c){
        return c-'a';
    }

    inline void ins(){
        int r = 1;
        for(int i=0;s[i];i++){
            int c = ind(s[i]);
            if(ch[r][c]==0)
                ch[r][c] = newNode();
            r = ch[r][c];
        }
        ++end[r];
    }

    inline void build(){
        queue<int> q;
        q.push(1);
        while(!q.empty()){
            int r = q.front();
            q.pop();
            rep(c,kind){
                int x = ch[r][c];
                if(!x)continue;
                q.push(x);
                int y = fail[r];
                while(y&&ch[y][c]==0)
                    y = fail[y];
                fail[x] = y?ch[y][c]:1;
                dp[x] = max( dp[r],dp[ fail[x] ] )+end[x];
            }
        }
        cout<<*max_element(dp+1,dp+tot+1)<<endl;
    }

    inline void run(){
        int n;
        while(RD(n),n){
            init();
            getchar();
            rep(i,n){
                gets(s);
                ins();
            }
            build();
        }
    }
}ac;

int main(){

#ifndef ONLINE_JUDGE
    freopen("sum.in","r",stdin);
    //freopen("sum.out","w",stdout);
#endif

    ac.run();

    return 0;
}
