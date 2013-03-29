/*

題目：
    小春现在很清闲,面对书桌上的N张牌,他决定给每张染色,目前小春只有3种
    颜色:红色,蓝色,绿色.他询问Sun有多少种染色方案,Sun很快就给出了答案.
    进一步,小春要求染出Sr张红色,Sb张蓝色,Sg张绝色.他又询问有多少种方
    案,Sun想了一下,又给出了正确答案. 最后小春发明了M种不同的洗牌法,这
    里他又问Sun有多少种不同的染色方案.两种染色方法相同当且仅当其中一种
    可以通过任意的洗牌法(即可以使用多种洗牌法,而每种方法可以使用多次)
    洗成另一种.Sun发现这个问题有点难度,决定交给你,答案可能很大,只要求
    出答案除以P的余数(P为质数).

    注意：
    输入数据保证任意多次洗牌都可用这 m种洗牌法中的一种代替，且对每种
    洗牌法，都存在一种洗牌法使得能回到原状态。

分析：
    題目中給定了很多置換群，在群置換下定義了等價類。所以我們可以用
    BurnSide引理來做。

    由於输入数据保证任意多次洗牌都可用这 m种洗牌法中的一种代替，且对每
    种洗牌法，都存在一种洗牌法使得能回到原状态。

    所以我們可以單獨對於每一個群來做。
    首先，給出群的每個循環的個數，記為b[1]...b[k]
    然後，dp之。
    dp[i][j][k] = sigma(dp[i-b[i]][j][k],dp[i][j-b[i]][k],dp[i][j][k-b[i]])

    對於不動群，即{(1)...(n)}，由重複計數原理可知：
    (sa+sb+sc)! / (sa! *sb! *sc!)
    數比較大，所以需要用到乘法的逆元來做。

    由BurnSide可知，最後需要除以m+1。

    問題得以解決。
	
	http://hi.baidu.com/aekdycoin/item/ed9d3c375a21f64e3075a1d5

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

/******** 程序部份 ********************/

const int MAXN = 25;

int dp[MAXN][MAXN][MAXN],inv[MAXN*3],p[MAXN*3];
int sa,sb,sc,m,mod;

int Mod(int a,int n){
    return (a%n+n)%n;
}
void ex_gcd(int a,int b,int &d,int &x,int &y){ /// 擴張歐几里得
    if(!b){
        d = a;
        x = 1;
        y = 0;
    }else{
        ex_gcd(b,a%b,d,y,x);
        y -= x*(a/b);
    }
}

int calinv(int a,int n){ /// 求逆元
    int d,x,y;
    ex_gcd(a,n,d,x,y);
    return d==1?Mod(x,n):-1;
}

void init(int n){
    p[0] = 1;
    rep1(i,n)
        p[i] = p[i-1]*i%mod;

    inv[1] = 1;
    REP(i,2,60)
        inv[i] = inv[i-1]*calinv(i,mod)%mod;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD3(sa,sb,sc);
    RD2(m,mod);

    int n = sa+sb+sc;

    init(n);

    int ans = p[n]*inv[sa]%mod *inv[sb]*inv[sc]%mod;

    int a[MAXN*3],b[MAXN*3];
    bool use[MAXN*3];
    int ncase = m;
    while(ncase--){
        rep1(i,n)
            RD(a[i]);
        memset(use,false,sizeof(use));
        memset(b,0,sizeof(b));
        int bcnt = 0;
        rep1(i,n){
            if(use[i])
                continue;
            ++ bcnt;
            use[i] = true;
            int x = a[i];
            b[bcnt] = 1;
            while(x!=i){
                use[x] = true;
                ++ b[bcnt];
                x = a[x];
            }
        }

        memset(dp,0,sizeof(dp));
        dp[0][0][0] = 1;
        rep1(q,bcnt)
        rep(i,sa+1)
            rep(j,sb+1)
                rep(k,sc+1){
                    int s = 0,y = b[q];
                    if(y<=i)
                        s += dp[i-y][j][k];
                    if(y<=j)
                        s += dp[i][j-y][k];
                    if(y<=k)
                        s += dp[i][j][k-y];
                    dp[i][j][k] = s%mod;
                }
        ans = (ans+dp[sa][sb][sc])%mod;
    }

    ans = ans*calinv(m+1,mod)%mod;

    cout<<ans<<endl;

	return 0;
}
