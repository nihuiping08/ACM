/*

題目：
    阿申准备报名参加GT考试，准考证号为N位数X1X2....Xn(0<=Xi<=9),他不希
    望准考证号上出现不吉利的数字。他的不吉利数学A1A2...Am(0<=Ai<=9)有M
    位，不出现是指X1X2...Xn中没有恰好一段等于A1A2...Am. A1和X1可以为0

分析：
    矩陣快速冪優化DP

    dp[i][j]表示當前字符串的位置為i，已經匹配成功了j位，則轉移方程為
    dp[i][j] = sigma( dp[i-1][k]*a[k][j] ) , 0<=k<m
    a[k][j]表示在位置k可以由a[k][j]個數字是的字符串匹配到位置j

    考慮KMP算法，當失配的時候可以由fail指針移向前面可以匹配的位置。
    所以我們可以通過枚舉輸入字符串的每個位置i，然後枚舉數字j，判斷在
    位置i+1上通過添加數字j可以匹配到的位置k，那麼a[i][k+1]++。如果不
    能夠通過失配指針找到相等的字符串的話，那麼a[i][0] ++。

    然後我們可以發現，可以對矩陣a進行矩陣快速冪運算。
    最後用列矩陣b乘上矩陣a，列矩陣b[0] = 1，其餘為0

    然後答案就是sigma(b[i]*a[i][j])

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

const int MAXN = 25;

int MOD,n,m;
char s[MAXN];
int fail[MAXN];

class Matrix{
    public:
        int n,m;
        int a[MAXN][MAXN];

        Matrix(){
            memset(a,0,sizeof(a));
        }
        Matrix(int _n,int _m):n(_n),m(_m){
            memset(a,0,sizeof(a));
        }

        Matrix operator * (Matrix p){
            int q = p.m;
            Matrix c(n,q);
            for(int i=0;i<n;i++)
                for(int k=0;k<q;k++)
                    if(a[i][k])
                        for(int j=0;j<m;j++)
                            c.a[i][j] = (c.a[i][j]+a[i][k]*p.a[k][j])%MOD;
            return c;
        }

        void setE(){
            for(int i=0;i<n;i++)
                a[i][i] = 1;
        }

        Matrix bin(int exp){
            Matrix temp(n,n);
            temp.setE();
            Matrix cur = *this;

            while(exp>0){
                if(exp&1)
                    temp = temp*cur;
                cur = cur*cur;
                exp = exp >> 1;
            }
            return temp;
        }

        void Debug(){
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)
                    cout<<a[i][j]<<" ";
                cout<<endl;
            }
            cout<<endl;
        }
};

void KMP(){
    fail[1] = 0;
    int j = 0;
    for(int i=2;s[i];i++){
        while(j>0&&s[i]!=s[j+1])
            j = fail[j];
        if(s[i]==s[j+1])
            j ++;
        fail[i] = j;
    }
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD3(n,m,MOD);
    scanf("%s",s+1);
    KMP();
    Matrix ans(m,m);

    rep(i,m){
        for(char c='0';c<='9';c++){
            int p = i;
            while(p>0&&s[p+1]!=c)
                p = fail[p];
            if(s[p+1]==c)
                ans.a[i][p+1] ++;
            else
                ans.a[i][0] ++;
        }
    }

    ans = ans.bin(n);

    int tmp = 0;
    rep(i,m)
        tmp = (tmp+ans.a[0][i])%MOD;

    cout<<tmp<<endl;

	return 0;
}
