/*

题目：
    直接求1+3^1+...+3^n的和

分析：
        构造矩阵matrix如下：
        A  1
        0  1
        我们发现matrix^(n+1)项的时候，第一行第二列就是问题所求
        所以在求A+A^2+A^3+...+A^k % p的时候，我们可以直接转化为对矩阵进行
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
const int MOD = 9999997;

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
    while(cin>>n){
        Matrix a = Matrix(2,MOD);
        a.init(3);
        a = a.pw(n);
        //a.di();
        ll ans = a.a[1][2]%MOD;
        cout<<ans<<endl;
    }
	return 0;
}
