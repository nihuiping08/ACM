/*

题目:
    小猫们看到蛋糕比饼干大之后，普遍认为蛋糕比饼干要好>.<。
    所以，如果Freda 给了第i 只小猫蛋糕且这个小猫是第一个吃
    到蛋糕的，那么就必须给第i+2,i+4,i+6......只小猫蛋糕。
    也就是说，如果存在正整数i,满足：
    1、对于所有的0<j<i,第j 只小猫吃到的是饼干
    2、第i 只小猫吃到的是蛋糕
    那么就必须有：
    对于所有的i<k<=N, k mod 2 = i mod 2,第k 只小猫吃到的是
    蛋糕。
    小猫的数目一多，Freda 就忙不过来了。请你帮忙计算，Freda
    一共有多少种可能的方法来招待这N 只小猫？

分析：
    如果只考虑第一只猫的话也可以慢慢推~
    全吃饼干：1种
    第n只吃蛋糕：……BBBBBD 1种
    第n-1只蛋糕：……BBBBD* 1*2种
      n-2      ：……BBBD*B 1*2
      n-3      ：……BBD*D* 1*2*2
      n-4      ：……BD*D*D 1*2*2
      n-5      ：……D*D*D* 1*2*2*2
    以此类推，那么答案就应该是
      ans=1+1+2+2+4+4+……+2^k ,因为有全饼干所以n+1项
    n+1为偶数时
      ans=2*(1+2+4+……+2^k)
      从2^0到2^k共(n+1)/2项，用等比数列求和公式
      ans=2*(1-2^((n+1)/2))/(1-2)=2^((n+3)/2)-2
    n+1为奇数时
      ans=2*(1+2+4+……+2^(k-1))+2^k
      括号里共n/2项包括2^0~2^(k-1)所以k-1=n/2-1即k=n/2
      再求和
      ans=2*(1-2^(n/2))/(1-2)+2^(n/2)=3*2^(n/2)-2
    剩下的就是快速幂取模……

*/
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int mod = 1000000007;

typedef __int64 ll;

ll pow(ll n,ll exp){
    ll ans = 1;
    while(exp>0){
        if(exp&1)
            ans = (ans*n)%mod;
        n = (n*n)%mod;
        exp = exp>>1;
    }
    return ans;
}

int main(){
    freopen("sum.in","r",stdin);
    ll n;

    while(cin>>n){
        int k = n>>1;
        ll ans;
        if(n&1)
            ans = (pow(2,k+2)-2)%mod;
        else
            ans = (3*pow(2,k)-2)%mod;
        cout<<ans<<endl;
    }
    return 0;
}
