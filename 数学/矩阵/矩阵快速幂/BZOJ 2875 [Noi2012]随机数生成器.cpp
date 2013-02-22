/*

题目：f[n+1] = (f[n]+c)%m , 给出f[0],n,m,c,g，求f[n]%g

分析：很明显可以构造矩阵
    A = a 1　　　　B = f[0]
        0 1　　　　　　 c
    但是由于数据太大了，所以在矩阵乘法中间计算时会溢出，所以我们需要在
    乘的时候做一下处理。改为跟快速幂乘法相似的计算方式来防止溢出。
    具体看代码

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

typedef unsigned long long ll;

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back

const int X = 5;

ll MOD;

class Matrix{
public:
    int n,m;
    ll a[X][X];

    ll cal(ll x,ll y){
        ll sum = 0;
        while(y>0){
            if(y&1)
                sum = (sum+x)%MOD;
            x = (x<<1)%MOD;
            y >>= 1;
        }
        return sum;
    }

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
            for(int j=0;j<q;j++)
                for(int k=0;k<m;k++)
                    c.a[i][j] = (c.a[i][j]+cal(a[i][k],p.a[k][j]))%MOD;
        return c;
    }

    void getE(){
        memset(a,0,sizeof(a));
        for(int i=0;i<n;i++)
            a[i][i] = 1;
    }

    Matrix bin(ll exp){
        Matrix temp(n,n);
        temp.getE();
        Matrix cur = *this;

        while(exp>0){
            if(exp&1)
                temp = temp*cur;
            cur = cur*cur;
            exp = exp >> 1;
        }
        return temp;
    }

    void di(){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++)
                cout<<a[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;
    }

};

int main(){

#ifndef ONLINE_JUDGE
	freopen("sum.in","r",stdin);
#endif

    ll m,a,c,x0,n,g;
    while(cin>>m>>a>>c>>x0>>n>>g){
        MOD = m;
        Matrix ans(2,2);
        ans.a[0][0] = a;
        ans.a[0][1] = ans.a[1][1] = 1;
        ans = ans.bin(n);
        //ans.di();
        Matrix temp(2,1);
        temp.a[0][0] = x0;
        temp.a[1][0] = c;
        ans = ans*temp;
        cout<<ans.a[0][0]%g<<endl;
    }
	return 0;
}
