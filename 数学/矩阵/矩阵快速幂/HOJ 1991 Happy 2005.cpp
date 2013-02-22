/*

题目：
    给出n，问2005^n的各个因子数之和对29取模

分析：
    2005 = 5*401，我们可以对于401进行分类：
    401^0 : 1     5       5^2      ... 5^n
    401^1 : 401   401*5   401*5^2  ... 401*5^n
    .
    .
    .
    401^n : 401^n 401^n*5 401^n*5^2 ... 401^n*5^n
    由此我们可以发现，问题可以转换为
    (1+401+401^2+...401^n)*(1+5+5^2+...+5^n)%29

    方法一：
        二分再二分。首先，a^n用一次二分，求和的时候再用一次二分。
        a^n二分的时候就是快速幂。
        求和二分：
        A+A^2+A...+A^(2k+1)=   A+A^2+...+A^k+A^(k+1)+A^(k+1)*(A+A^2+...+A^k).
        A+A^2+...+A^2k     =   A+A^2+...+A^k+A^k*(A+A^2+...+A^k).
    方法二：
        构造矩阵matrix如下：
        A  1
        0  1
        我们发现matrix^(n+1)项的时候，第一行第二列就是问题所求
        所以在求A+A^2+A^3+...+A^k % 29的时候，我们可以直接转化为对矩阵进行
        快速幂取模。
    我下面的代码为构造矩阵求解。。。

*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long ll;

#define debug puts("here");

const int X = 3;
const int MOD = 29;

struct Matrix{

    ll a[X][X];
    int n;
    int mod;

    Matrix(){}
    Matrix(int _n,int _mod):n(_n),mod(_mod){
        memset(a,0,sizeof(a));
    }

    void setE(){
        memset(a,0,sizeof(a));
        for(int i=1;i<=n;i++)
            a[i][i] = 1;
    }

    Matrix operator * (Matrix p){
        Matrix c(n,mod);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                for(int k=1;k<=n;k++){
                    c.a[i][j] += a[i][k]*p.a[k][j];
                    c.a[i][j] %= mod;
                }
        return c;
    }

    Matrix pw(int exp){
        Matrix cur = *this;
        Matrix c(n,MOD);
        c.setE();
        while(exp>0){
            if(exp&1)
                c = c*cur;
            cur = cur*cur;
            exp = exp>>1;
        }
        return c;
    }

    void di(){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                cout<<a[i][j]<<" ";
            cout<<endl;
        }
    }

    void init(int x){
        a[1][2] = a[2][2] = 1;
        a[2][1] = 0;
        a[1][1] = x;
    }
}matrix;

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    ll n;
    while(cin>>n,n){
        Matrix a = Matrix(2,MOD);
        a.init(5);
        a = a.pw(n+1);
        ll ans = a.a[1][2]%MOD;

        a.init(401);
        a = a.pw(n+1);
        ans = ans*a.a[1][2]%MOD;
        cout<<ans<<endl;
    }
	return 0;
}
