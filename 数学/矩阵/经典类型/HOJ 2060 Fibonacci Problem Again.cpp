/*

题目：
    计算斐波那契数列[a,b]的和值对于1e9取模

分析：
    对于斐波那契求第n项，我们可以构造矩阵
    A = 1 1  B = f[n]
        1 0      f[n-1]
    则f[n]为矩阵 A^n * B的第一项

    对于这题，我们可以额外构造多一维的矩阵出来为
        1 1 0           f[n]
    A = 1 0 0      B =  f[n-1]
        1 0 1           sum[n-1]
    我们同样可以算出 sum[n] = A^n * B 的第三项

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

#define debug puts("here")
#define rep(i,n) for(int i=0;i<n;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back

const int X = 5;
const ll MOD = 1e9;

class Matrix{
public:
    int n,m;
    ll a[X][X];

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
                    c.a[i][j] = (c.a[i][j]+a[i][k]*p.a[k][j])%MOD;
        return c;
    }

    void getE(){
        memset(a,0,sizeof(a));
        for(int i=0;i<n;i++)
            a[i][i] = 1;
    }

    Matrix bin(int exp){
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

    int n,m;
    while(scanf("%d%d",&n,&m),n||m){
        Matrix a = Matrix(3,3);
        a.a[0][0] = a.a[0][1] = a.a[1][0] = a.a[2][0] = a.a[2][2] = 1;

        Matrix f = Matrix(3,1);
        f.a[0][0] = 1;
        f.a[1][0] = 1;
        f.a[2][0] = 1;

        ll pre = 0;
        ll now = 0;
        if(n){
            Matrix x = a.bin(n-1);
            x = x*f;
            pre = x.a[2][0];
        }
        Matrix y = a.bin(m);
        y = y*f;
        now = y.a[2][0];
        ll mod = ll(1000000000);
        cout<<(now-pre+mod)%mod<<endl;
    }
	return 0;
}
