/*

題目：
    如果一個數的各位數字均為a或者b，則這數為good number。如果一個good
    number的各數字和為good number的話，這個數為excellent。給出a b以及
    數的長度為len，問長度為len的數中有多少個excellent數

分析：
    比較明顯的組合數。
    我們可以枚舉有i個a，然後剩餘len-i個b。
    如果a*i+(len-i)*b為good，我們可以從len個位置中選出i個位置放a，
    剩餘的len-i個位置放b。所以當前的組合數為C(len,i)。
    答案即為sigma(C(len,k)),a*k+(len-k)*b為good
    由於len比較大，所以我們需要進行優化。
    C(n,i) = n!/( m!*(n-m)! )
    所以我們可以通過求( m!*(n-m)! )的逆元inv，然後n!*inv即為組合數
    由於題目時間限制還是比較緊，所以我們需要預處理出階乘

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long ll;

#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)

#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)

/******** program ********************/

const int MOD = 1e9+7;
const int MAXN = 1e6+5;

int a,b,len;
ll fac[MAXN];

bool ok(int n){
    while(n){
        int t = n%10;
        if(t!=a&&t!=b)
            return false;
        n /= 10;
    }
    return true;
}

ll Ext_gcd(ll a,ll b,ll &x,ll &y){
    if(b==0){
        x = 1;
        y = 0;
        return a;
    }
    ll res = Ext_gcd(b,a%b,y,x);
    y -= a/b*x;
    return res;
}

ll Inv(ll a){ // 擴展歐几里得求逆元
    ll d,x,y;
    d = Ext_gcd(a,MOD,x,y);
    if (d==1) return (x%MOD+MOD)%MOD;
    return -1;
}

ll C(int n,int m){//组合数公式:n!/( (n-m)!*m! ) = n!*inv( (n-m)!*m! )
    return fac[n]*Inv(fac[m]*fac[n-m]%MOD)%MOD;
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
	//freopen("sum.out","w",stdout);
#endif

    RD3(a,b,len);

    fac[0] = 1;
    rep1(i,len)
        fac[i] = fac[i-1]*i%MOD;
    ll ans = 0;

    for(int i=0;i<=len;i++)
        if( ok(i*a+(len-i)*b) )
            ans += C(len,i);
    printf("%I64d\n",ans%MOD);

	return 0;
}
